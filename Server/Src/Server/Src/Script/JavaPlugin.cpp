#include "stdafx.h"
#include <Script/JavaPlugin.h>

namespace Skyrim
{
	namespace Script
	{
		//---------------------------------------------------------------------------------------
		JavaPlugin::JavaPlugin(const std::string& pPath, JavaManager& pManager, JavaPluginManager& pPluginManager)
			:mManager(pManager), mPluginManager(pPluginManager)
		{
			jstring mainClass = pManager.GetMainClassName((char*)pPath.c_str());
			if(mainClass)
			{
				const char* rawStr = pManager.GetJNI()->GetStringUTFChars(mainClass,0);
				std::string str(rawStr);
				pManager.GetJNI()->ReleaseStringUTFChars(mainClass,rawStr);

				for(size_t i = 0; i < str.size(); ++i)
				{
					if(str[i] == '.') str[i] = '/';
				}
				mJavaClass = pManager.GetJNI()->FindClass(str.c_str());

				if(mJavaClass)
				{
					auto constructor = pManager.GetJNI()->GetMethodID(mJavaClass, "<init>", "()V");
					if(constructor)
					{
						mJavaObject = pManager.GetJNI()->NewObject(mJavaClass,constructor);
						if(mJavaObject)
						{
							auto func = mManager.GetJNI()->GetMethodID	 (mJavaClass, "setPluginManager",
								"(Lcom/skyrimonline/PluginManager;)V");
							if(func)
								mManager.GetJNI()->CallVoidMethod(mJavaObject, func, mPluginManager.GetJava());

							func = mManager.GetJNI()->GetMethodID(mJavaClass, "setPointer", "(J)V");
							if(func)
								mManager.GetJNI()->CallVoidMethod(mJavaObject, func, (jlong)this);

							mOnEnable = mManager.GetJNI()->GetMethodID(mJavaClass, "onEnable", "()V");
							mOnDisable = mManager.GetJNI()->GetMethodID(mJavaClass, "onDisable", "()V");
							mOnNewShard = mManager.GetJNI()->GetMethodID(mJavaClass, "onNewShard", "(Lcom/skyrimonline/game/World;)V");
						}
					}
					else
						System::Log::GetInstance()->Error(str + " constructor not found !");
				}
				else
					System::Log::GetInstance()->Error(str + " not found !");
			}
		}
		//---------------------------------------------------------------------------------------
		void JavaPlugin::OnEnable()
		{
			if(mJavaObject && mOnEnable)
				mManager.GetJNI()->CallVoidMethod(mJavaObject, mOnEnable);
			Error();
		}
		//---------------------------------------------------------------------------------------
		void JavaPlugin::OnDisable()
		{
			if(mJavaObject && mOnDisable);
			//mManager.GetJNI()->CallVoidMethod(mJavaObject,mManager.GetJNI()->GetMethodID(mJavaClass, "onDisable", "()V"));
			Error();
		}
		//---------------------------------------------------------------------------------------
		void JavaPlugin::OnNewShard(Game::IWorld* world)
		{
			if(mJavaObject && mOnNewShard)
				mManager.GetJNI()->CallVoidMethod(mJavaObject, mOnNewShard, world->GetJava());
			Error();
		}
		//---------------------------------------------------------------------------------------
		void JavaPlugin::Error()
		{
			if (mManager.GetJNI()->ExceptionOccurred()) {
				mManager.GetJNI()->ExceptionDescribe();
			}
		}
		//---------------------------------------------------------------------------------------
	}
}