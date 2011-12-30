#include "stdafx.h"
#include <Script/JavaPluginManager.h>
#include <Script/PluginManager.h>

namespace Skyrim
{
	namespace Script
	{
		//---------------------------------------------------------------------------------------
		JavaPluginManager::JavaPluginManager(JavaManager& pManager, PluginManager& pPlugins)
			:mManager(pManager),mPlugins(pPlugins)
		{
			mJavaClass = pManager.GetJNI()->FindClass("com/skyrimonline/PluginManager");
			if (pManager.GetJNI()->ExceptionOccurred()) {
				pManager.GetJNI()->ExceptionDescribe();
			}
			if(mJavaClass)
			{
				auto constructor = pManager.GetJNI()->GetMethodID(mJavaClass, "<init>", "()V");
				if(constructor)
				{
					mJavaObject = pManager.GetJNI()->NewObject(mJavaClass,constructor);
					if(mJavaObject)
					{
						auto func = mManager.GetJNI()->GetMethodID(mJavaClass, "setPointer", "(J)V");
						mManager.GetJNI()->CallVoidMethod(mJavaObject, func, (jlong)this);
						mInstance = this;
					}
				}
				else
					System::Log::GetInstance()->Error("com.skyrimonline.PluginManager constructor not found !");
			}
			else
				System::Log::GetInstance()->Error("com.skyrimonline.PluginManager not found !");
		}
		//---------------------------------------------------------------------------------------
		jobject JavaPluginManager::GetJava()
		{
			return mJavaObject;
		}
		//---------------------------------------------------------------------------------------
		void JavaPluginManager::Register(void* handle, int event)
		{
			mPlugins.Register((Plugin*)handle, event);
		}
		//---------------------------------------------------------------------------------------
	}
}