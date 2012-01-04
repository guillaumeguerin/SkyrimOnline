#pragma once

#include <Script/JavaManager.h>
#include <Script/JavaPluginManager.h>
#include <Game/IWorld.h>

namespace Skyrim
{
    namespace Script
    {
		class Plugin;
        /**
		* Plugin manager
		*/
		class PluginManager
		{
		public:

			typedef std::list<Plugin*> Listeners;

			enum Event{
				SERVER = 1,
				WORLD = 2
			};

			PluginManager():
			  mPluginManager(nullptr),mJava(nullptr)
			{};

			~PluginManager()
			{
				delete mPluginManager;
				delete mJava;
			};

			static PluginManager& GetInstance();

			JavaManager& GetJavaManager();

			void Initialize();
			void Free();

			void AddShard(Game::IWorld* world);

			void Register(Plugin* plugin, int event);

		private:

			std::list<std::tuple<Plugin*,std::string>> mPlugins;
			std::list<HMODULE>  mSharedObjects;
			JavaManager* mJava;

			Listeners mServerListeners;
			Listeners mWorldListeners;

			JavaPluginManager* mPluginManager;

			static PluginManager* mInstance;
		};
    }
}