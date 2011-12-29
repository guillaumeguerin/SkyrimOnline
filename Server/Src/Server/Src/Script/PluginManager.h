#pragma once

#include <Script/JavaManager.h>

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

			void Initialize();
			void Free();

		private:

			std::list<std::tuple<Plugin*,std::string>>  mPlugins;
			std::list<HMODULE>  mSharedObjects;
			JavaManager* mJava;
		};
    }
}