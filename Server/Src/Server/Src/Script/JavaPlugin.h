#pragma once

#include <Script/Plugin.h>
#include <Script/JavaManager.h>

namespace Skyrim
{
	namespace Script
	{
		class JavaPlugin : public Plugin
		{
		public:

			JavaPlugin(const std::string& pPath, JavaManager& pManager);

			__declspec(nothrow) void OnEnable();
			__declspec(nothrow) void OnDisable();

		private:

			jobject mJavaObject;
			jclass mJavaClass;
			jmethodID mOnEnable, mOnDisable, mOnChat;
			JavaManager& mManager;
		};
	}
}