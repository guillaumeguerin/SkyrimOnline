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
			mJavaClass = pManager.GetJNI()->FindClass(pManager.GetJNI()->GetStringUTFChars(pManager.GetMainClassName((char*)pPath.c_str()), 0));
			mJavaObject = pManager.GetJNI()->NewObject(mJavaClass,pManager.GetJNI()->GetMethodID(mJavaClass, "<init>", "()V"));

			mManager.GetJNI()->GetMethodID(mJavaClass, "onEnable", "()V");
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