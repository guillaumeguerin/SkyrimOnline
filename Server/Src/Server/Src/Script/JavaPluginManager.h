#pragma once

#include <Script/JavaManager.h>
#include <IPluginManager.h>

namespace Skyrim
{
	namespace Script
	{
		class JavaPluginManager : public IPluginManager
		{
		public:

			JavaPluginManager(JavaManager& pManager, class PluginManager& pPlugins);

			jobject GetJava();

			void Register(void* handle, int event);

		private:

			jobject mJavaObject;
			jclass mJavaClass;
			JavaManager& mManager;
			class PluginManager& mPlugins;
		};
	}
}