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
#include <Game/TimeManager.h>
#include <Game/WeatherManager.h>
#include <Script/PluginManager.h>
#include <Game/IWorld.h>
#include <System/Job.h>

namespace Skyrim
{
	namespace Network
	{
		class Server;
	}
	namespace Game
	{
		class World :
			public IWorld,
			public System::Job
		{
		public:

			World(const std::string& pName, bool pPersistent, Network::Server* pServer);

			void Work();

			void Start();

			void Add(Network::Session::pointer pPlayer);
			void Remove(Network::Session::pointer pPlayer);

			void DispatchPlayerMoveAndLook(Network::Session::pointer pPlayer);
			void DispatchToAll(Network::Packet&);
			void DispatchToAllButMe(Network::Packet&, Network::Session::pointer pPlayer);

			bool IsMarkedForDelete();
			std::string GetName();

			unsigned int Count();

			void CreateJava();

		protected:

			void SendTimeSync(Network::Session::pointer pPlayer);
			void SendWeatherSync(Network::Session::pointer pPlayer);

		private:

			bool mPersistant;
			std::string mName;
			std::deque<Network::Session::pointer> mSessions;
			boost::mutex mGuard, mReleaseGuard;
			boost::timer mTimer;
			bool mScheduled;

			Network::Server* mServer;

			// Actual gameplay related
			TimeManager mTimeManager;
			WeatherManager mWeatherManager;
		};
	}
}