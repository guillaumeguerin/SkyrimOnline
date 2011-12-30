/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#pragma once

#include <Network/Session.h>
#include <System/EventListener.h>
#include <System/DBWorkQueue.h>
#include <System/WorkQueue.h>
#include <Game/World.h>
#include <Script/PluginManager.h>

namespace Skyrim
{
	namespace Network
	{
		class Server
			: public System::EventListener,
			  public std::enable_shared_from_this<Server>
		{
		public:

			/**
			 * Instanticate the server
			 * @param pPort The port to start the server on
			 */
			Server(unsigned short pPort);
			/**
			 * Start the server, will return on exit
			 */
			void Start();
			/**
			 * Authentication and sync loop
			 */
			void Run();
			/**
			 * Stops the server, Run will return
			 */
			void Stop();

			/**
			 * Drops a player from the server, must never be called !
			 * @param pSession The session to drop from the server and world
			 */
			void Remove(Session::pointer pSession);

			/**
			 * Get the database work queue, needed to load a DAO
			 * @return the database work queue
			 */
			System::DBWorkQueue* GetDatabaseWorkQueue();

			/**
			 * Get the work queue, needed for every task, increase performance over thread instancing
			 * @return the work queue
			 */
			System::WorkQueue*	 GetWorkQueue();

			virtual void OnEvent(std::shared_ptr<System::Event> pEvent);

			/**
			 * Get the current player count
			 * @return The current player count
			 */
			unsigned int Count();

			/**
			 * Get the maximum amount of players on the server
			 * @return The peak amount of players
			 */
			unsigned int Peak();

			/**
			 * Send a packet to everybody on this server
			 * @param packet The packet to send
			 */
			void DispatchToAll(Packet& packet);

			/**
			 * Sends a packet to every player except for the player specified
			 * @param packet The packet to send
			 * @param pPlayer The player to discard while sending
			 */
			void DispatchToAllButMe(Packet& packet, Session::pointer pPlayer);

			/**
			 * Send the shard list to the specified player
			 * @param pPlayer The player to send to
			 */
			void SendShardList(Session::pointer pPlayer);

			/**
			 * Moves a player from authentication to a world
			 * @param pWorldIndex The world's name
			 * @param pPlayer The player to move
			 */
			void MoveToWorld(const std::string& pWorldIndex, Session::pointer pPlayer);

			/**
			 * Add a shard to the server
			 * @param pWorld The world to add
			 */
			void AddShard(Game::IWorld* pWorld);

		protected:

			void Accept();
			void HandleAccept(Session::pointer pSession, const boost::system::error_code& pError);

			/**
			 * Scale the thread count according to the runtime infos.
			 */
			void Scale();

		private:

			boost::asio::ip::tcp::acceptor mAcceptor;

			boost::mutex							mGuard;
			std::deque<Session::pointer>			mSessions;

			std::map<std::string,Game::IWorld*>		mWorlds; //< Be carefull with worlds, they can be fully abstract and run remotelly
			System::DBWorkQueue* mDBWorkQueue;
			System::WorkQueue*   mWorkQueue;

			unsigned int mMaxConnections;

			bool mStarted;

			unsigned int mID;
		};
	}
}