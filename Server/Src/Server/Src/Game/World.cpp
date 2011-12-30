/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include "World.h"
#include <Network/Packet.h>
#include <Network/Server.h>

namespace Skyrim{
	namespace Game
	{
		//---------------------------------------------------------------------
		World::World(const std::string& pName, bool pPersistant, Network::Server* pServer)
			:mName(pName), mPersistant(pPersistant), mServer(pServer)
		{
		}
		//---------------------------------------------------------------------
		void World::Work()
		{
			float elapsed = (float)mTimer.elapsed();
			if(mSessions.size() > 0)
			{
				mTimeManager.Update(elapsed);

				mTimer.restart();
				mGuard.lock();
				auto sessionCopy(mSessions);
				mGuard.unlock();

				std::for_each(sessionCopy.begin(), sessionCopy.end(),
					[this](Network::Session::pointer pSession)
				{
					pSession->Run();
				});
			}
			else if(elapsed > 120)
			{
				mScheduled = false;
				return;
			}

			mServer->GetWorkQueue()->Add(this);

			boost::this_thread::yield();
		}
		//---------------------------------------------------------------------
		void World::Add(Network::Session::pointer pPlayer)
		{
			{
				boost::mutex::scoped_lock lock(mGuard);
				mSessions.push_back(pPlayer);
			}
			{
				boost::mutex::scoped_lock(mReleaseGuard);
				if(!mScheduled)
				{
					mScheduled = true;
					mServer->GetWorkQueue()->Add(this);
				}
			}

			pPlayer->SetWorld(this);

			Network::Packet packet;
			packet.Opcode = SMSG_SHARD_HANDSHAKE;
			packet.Push((unsigned int)1);
			pPlayer->Write(packet);

			SendTimeSync(pPlayer);
			SendWeatherSync(pPlayer);
		}
		//---------------------------------------------------------------------
		void World::Remove(Network::Session::pointer pPlayer)
		{
			boost::mutex::scoped_lock lock(mGuard);
			auto itor = std::find(mSessions.begin(), mSessions.end(), pPlayer);
			if(itor != mSessions.end())
			{
				std::for_each(mSessions.begin(), mSessions.end(),
					[this,&pPlayer](Network::Session::pointer pSession)
				{
					pSession->Remove(pPlayer);
				});

				mSessions.erase(itor);
			}
		}
		//---------------------------------------------------------------------
		void World::DispatchPlayerMoveAndLook(Network::Session::pointer pPlayer)
		{
			boost::mutex::scoped_lock lock(mGuard);

			std::for_each(mSessions.begin(), mSessions.end(),
				[this,&pPlayer](Network::Session::pointer pSession)
			{
				if(pSession != pPlayer)
				{
					pSession->HandlePlayerEvent(pPlayer);
				}
			});
		}
		//---------------------------------------------------------------------
		void World::DispatchToAll(Network::Packet& data)
		{
			boost::mutex::scoped_lock lock(mGuard);

			std::for_each(mSessions.begin(), mSessions.end(),
				[this,&data](Network::Session::pointer pSession)
			{
				pSession->Write(data);
			});
		}
		//---------------------------------------------------------------------
		void World::DispatchToAllButMe(Network::Packet& data, Network::Session::pointer pPlayer)
		{
			boost::mutex::scoped_lock lock(mGuard);

			std::for_each(mSessions.begin(), mSessions.end(),
				[this,&pPlayer,&data](Network::Session::pointer pSession)
			{
				if(pSession != pPlayer)
				{
					pSession->Write(data);
				}
			});
		}
		//---------------------------------------------------------------------
		bool World::IsMarkedForDelete()
		{
			return (mTimer.elapsed() >= 180 && !mPersistant);
		}
		//---------------------------------------------------------------------
		std::string World::GetName()
		{
			return mName;
		}
		//---------------------------------------------------------------------
		unsigned int World::Count()
		{
			return static_cast<unsigned int>(mSessions.size());
		}
		//---------------------------------------------------------------------
		void World::CreateJava()
		{
			auto javaclass = Script::PluginManager::GetInstance().GetJavaManager().GetJNI()->FindClass("com/skyrimonline/game/World");
			if(javaclass)
			{
				auto constructor = Script::PluginManager::GetInstance().GetJavaManager().GetJNI()->GetMethodID(javaclass, "<init>", "()V");
				if(constructor)
				{
					mJavaObject = Script::PluginManager::GetInstance().GetJavaManager().GetJNI()->NewObject(javaclass,constructor);
					if(mJavaObject)
					{
						auto func = Script::PluginManager::GetInstance().GetJavaManager().GetJNI()->GetMethodID(javaclass, "setPointer", "(J)V");
						if(func)
							Script::PluginManager::GetInstance().GetJavaManager().GetJNI()->CallVoidMethod(mJavaObject, func, (jlong)this);
					}
				}
				else
					System::Log::GetInstance()->Error("com.skyrimonline.game.world constructor not found !");
			}
			else
				System::Log::GetInstance()->Error("com.skyrimonline.game.world not found !");
		}
		//---------------------------------------------------------------------
	}
}