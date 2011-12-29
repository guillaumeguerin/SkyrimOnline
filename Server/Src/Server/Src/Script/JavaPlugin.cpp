#include "stdafx.h"
#include <Script/JavaPlugin.h>

namespace Skyrim
{
	namespace Script
	{
		//---------------------------------------------------------------------------------------
		JavaPlugin::JavaPlugin(const std::string& pPath, JavaManager& pManager)
			:mManager(pManager)
		{
			jstring mainClass = pManager.GetMainClassName((char*)pPath.c_str());
			if(mainClass)
			{
				std::string str = pManager.GetJNI()->GetStringUTFChars(mainClass,0);
				for(size_t i = 0; i < str.size(); ++i)
				{
					if(str[i] == '.') str[i] = '/';
				}
				mJavaClass = pManager.GetJNI()->FindClass(str.c_str());
				if (pManager.GetJNI()->ExceptionOccurred()) {
					pManager.GetJNI()->ExceptionDescribe();
				}
				if(mJavaClass)
				{
					auto constructor = pManager.GetJNI()->GetMethodID(mJavaClass, "<init>", "()V");
					if(constructor)
						mJavaObject = pManager.GetJNI()->NewObject(mJavaClass,constructor);
					else
						std::cout << "no constructor" << std::endl;
				}
				else
					std::cout << "not found" << std::endl;
			}
		}
		//---------------------------------------------------------------------------------------
		void JavaPlugin::OnEnable()
		{
			mManager.GetJNI()->CallVoidMethod(mJavaObject,mManager.GetJNI()->GetMethodID(mJavaClass, "onEnable", "()V"));
		}
		//---------------------------------------------------------------------------------------
		void JavaPlugin::OnDisable()
		{
			//mManager.GetJNI()->CallVoidMethod(mJavaObject,mManager.GetJNI()->GetMethodID(mJavaClass, "onDisable", "()V"));
		}
		//---------------------------------------------------------------------------------------
	}
}