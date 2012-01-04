#pragma once

#include <Script/Plugin.h>
#include <Script/JavaManager.h>
#include <Script/JavaPluginManager.h>

namespace Skyrim
{
	namespace Script
	{
		class JavaPlugin : public Plugin
		{
		public:

			JavaPlugin(const std::string& pPath, JavaManager& pManager, JavaPluginManager& pPluginManager);

			__declspec(nothrow) void OnEnable();
			__declspec(nothrow) void OnDisable();

			__declspec(nothrow) void OnNewShard(Game::IWorld*);

			void Error();

		private:

			jobject mJavaObject;
			jclass mJavaClass;
			jmethodID mOnEnable, mOnDisable, mOnNewShard;
			JavaManager& mManager;
			JavaPluginManager& mPluginManager;
		};
	}
}