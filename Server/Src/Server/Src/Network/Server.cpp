/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include <Network/Server.h>

using boost::asio::ip::tcp;

namespace Skyrim
{
	namespace Network
	{
		//---------------------------------------------------------------------
		Server::Server(unsigned short pPort)
			:mAcceptor(*new boost::asio::io_service, tcp::endpoint(tcp::v4(), pPort)),
			mStarted(false), mID(0),mMaxConnections(0)
		{
			System::Log::GetInstance()->Print("                            Skyrim Online         ");
			System::Log::GetInstance()->Print("Memory model : " + std::to_string((unsigned long long)sizeof(void*) * 8) + " bits				   ");
		}
		//---------------------------------------------------------------------
		void Server::Scale()
		{
			/**
			 * 1 database thread for 3 event threads if enough hardware threads
			 * 1 network thread for ever !!!!!!
			 */
			unsigned int logicThreads = boost::thread::hardware_concurrency();
			unsigned int dbThreads = 1;
			unsigned int coreThreads = 1;
			if(logicThreads > 3)
			{
				dbThreads = (float)logicThreads / 3.f + 1;
				coreThreads = logicThreads - dbThreads;
			}
			mDBWorkQueue = new System::DBWorkQueue(dbThreads);
			mWorkQueue   = new System::WorkQueue(coreThreads);
			new boost::thread([this]() -> void{mAcceptor.get_io_service().run();});

			System::Log::GetInstance()->Print("Running with : - " + std::to_string((unsigned long long)dbThreads) + " Database thread(s)				               ");
			System::Log::GetInstance()->Print("               - 1 Network thread                                ");
			System::Log::GetInstance()->Print("               - " + std::to_string((unsigned long long)coreThreads) + " Logic thread(s)                                  ");
			System::Log::GetInstance()->Print("");
		}
		//---------------------------------------------------------------------
		void Server::Start()
		{
			// Instanciate the plugins
			Script::PluginManager::GetInstance();

			Session::Setup();

			AddShard(new Game::World("Skyrim Online English", true, this));
			AddShard(new Game::World("Skyrim Online Others", true, this));

			Accept();
			Scale();

			auto end = mWorlds.end();
			for(auto itor = mWorlds.begin(); itor != end; ++itor)
			{
				itor->second->Start();
			}

			System::Log::GetInstance()->Print("Waiting for connections.");
			mStarted = true;

			Run();
		}
		//---------------------------------------------------------------------
		void Server::Run()
		{
			while(1)
			{
				// This thread doesn't need to be very responsive
				Sleep(10);

				long time = clock();
				mGuard.lock();
				auto sessionCopy(mSessions);
				mGuard.unlock();

				// Work with authenticating sessions
				std::for_each(sessionCopy.begin(), sessionCopy.end(),
					[this](Session::pointer pSession)
				{
					// Run must be synchronous
					pSession->Run();
				});

				// Go through world and delete dead ones
				auto end = mWorlds.end();
				for(auto itor = mWorlds.begin(); itor != end; ++itor)
				{
					if((itor)->second->IsMarkedForDelete())
					{
						delete (itor)->second;
						itor = mWorlds.erase(itor);
					}
				}

				System::Log::GetInstance()->Update();
			}
		}
		//---------------------------------------------------------------------
		void Server::Stop()
		{
		}
		//---------------------------------------------------------------------
		System::DBWorkQueue* Server::GetDatabaseWorkQueue()
		{
			return mDBWorkQueue;
		}
		//---------------------------------------------------------------------
		System::WorkQueue* Server::GetWorkQueue()
		{
			return mWorkQueue;
		}
		//---------------------------------------------------------------------
		void Server::Accept()
		{
			Session::pointer session = boost::make_shared<Session>(mAcceptor.get_io_service(), this);
			mAcceptor.async_accept(session->GetSocket(),
				boost::bind(&Server::HandleAccept, this,
				session, boost::asio::placeholders::error));
		}
		//---------------------------------------------------------------------
		void Server::Remove(Session::pointer pPlayer)
		{
			boost::mutex::scoped_lock lock(mGuard);

			auto itor = std::find(mSessions.begin(), mSessions.end(), pPlayer);
			if(itor != mSessions.end())
			{
				mSessions.erase(itor);
			}
			else
			{
				pPlayer->GetWorld()->Remove(pPlayer);
			}
		}
		//---------------------------------------------------------------------
		void Server::HandleAccept(Session::pointer pSession, const boost::system::error_code& pError)
		{
			if(!pError)
			{
				mGuard.lock();
				mSessions.push_back(pSession);
				mGuard.unlock();

				pSession->Start();
			}
			else
			{
				std::cerr << pError.message().c_str() << std::endl;
			}
			Accept();
		}
		//---------------------------------------------------------------------
		unsigned int Server::Count()
		{
			unsigned int total = (unsigned int)mSessions.size();
			auto end = mWorlds.end();
			for(auto itor = mWorlds.begin(); itor != end; ++itor)
			{
				total += itor->second->Count();
			}
			mMaxConnections = std::max(total,mMaxConnections);
			return total;
		}
		//---------------------------------------------------------------------
		unsigned int Server::Peak()
		{
			return mMaxConnections;
		}
		//---------------------------------------------------------------------
		void Server::SendShardList(Session::pointer pPlayer)
		{
			Packet packet;
			packet.Opcode = SMSG_SHARD_LIST;
			packet.Push((unsigned int)mWorlds.size());

			auto end = mWorlds.end();
			unsigned int i = 0;
			for(auto itor = mWorlds.begin(); itor != end; ++itor)
			{
				packet.Push(itor->second->GetName());
				packet.Push((unsigned int)0);
				++i;
			}
			pPlayer->Write(packet);
		}
		//---------------------------------------------------------------------
		void Server::MoveToWorld(const std::string& pWorldIndex, Session::pointer pPlayer)
		{
			{
				boost::mutex::scoped_lock lock(mGuard);

				auto itor = std::find(mSessions.begin(), mSessions.end(), pPlayer);
				if(itor != mSessions.end())
					mSessions.erase(itor);
			}
			auto world = mWorlds[pWorldIndex];
			if(world)
			{
				reinterpret_cast<Game::World*>(world)->Add(pPlayer);
			}
		}
		//---------------------------------------------------------------------
		void Server::AddShard(Game::IWorld* pWorld)
		{
			Script::PluginManager::GetInstance().AddShard(pWorld);
			mWorlds[pWorld->GetName()] = pWorld;
		}
		//---------------------------------------------------------------------
		void Server::OnEvent(std::shared_ptr<System::Event> pEvent)
		{
			if(!mStarted)
			{
				mGuard.unlock();
			}
		}
		//---------------------------------------------------------------------
	}
}