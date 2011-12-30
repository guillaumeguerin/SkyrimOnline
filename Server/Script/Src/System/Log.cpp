/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include "Log.h"
#include "LogJNI.h"

using namespace boost::posix_time;
using namespace boost::gregorian;

JNIEXPORT void JNICALL Java_com_skyrimonline_system_Log_Debug
	(JNIEnv * env, jobject obj, jstring str)
{
	const char *nativeString = env->GetStringUTFChars(str, 0);

	Skyrim::System::Log::GetInstance()->Debug(nativeString);

	env->ReleaseStringUTFChars(str, nativeString);
}

JNIEXPORT void JNICALL Java_com_skyrimonline_system_Log_Error
	(JNIEnv *env , jobject obj, jstring str)
{
	const char *nativeString = env->GetStringUTFChars(str, 0);

	Skyrim::System::Log::GetInstance()->Error(nativeString);

	env->ReleaseStringUTFChars(str, nativeString);
}

JNIEXPORT void JNICALL Java_com_skyrimonline_system_Log_Print
  (JNIEnv *env , jobject obj, jstring str)
{
	const char *nativeString = env->GetStringUTFChars(str, 0);

	Skyrim::System::Log::GetInstance()->Print(nativeString);

	env->ReleaseStringUTFChars(str, nativeString);
}

namespace Skyrim
{
	namespace System
	{
		//---------------------------------------------------------------------
		#pragma data_seg (".shared" )
		Log* Log::mInstance = nullptr;
		#pragma data_seg ()
		//---------------------------------------------------------------------
		Log::Log()
			:mLevel(VERBOSE)
		{
			mLog.open("Server.log",std::ios::trunc);
		}
		//---------------------------------------------------------------------
		Log* Log::GetInstance()
		{
			if(!mInstance)
				mInstance = new Log;
			return mInstance;
		}
		//---------------------------------------------------------------------
		void Log::Print(const std::string& pData)
		{
			if(mLevel <= NONE)
				return;
			mToLog.push(std::make_pair(0,pData));
		}
		//---------------------------------------------------------------------
		void Log::Debug(const std::string& pData)
		{
			if(mLevel < VERBOSE)
				return;

			mToLog.push(std::make_pair(2,pData));
		}
		//---------------------------------------------------------------------
		void Log::Error(const std::string& pData)
		{
			if(mLevel < LOW)
				return;

			mToLog.push(std::make_pair(1,pData));
		}
		//---------------------------------------------------------------------
		void Log::PrintTime()
		{
			ptime now = second_clock::local_time();
			mLog << to_simple_string(now.date()) << " ";
		}
		//---------------------------------------------------------------------
		void Log::SetLevel(Level pLevel)
		{
			mLevel = pLevel;
		}
		//---------------------------------------------------------------------
		void Log::Update()
		{
			std::pair<int, std::string> log;
			while(mToLog.try_pop(log))
			{
				PrintTime();
				switch(log.first)
				{
				case 0:mLog << log.second << std::endl;std::cout << log.second << std::endl;break;
				case 1:mLog << "[ERROR] "<< log.second << std::endl;std::cout << "[ERROR] "<< log.second << std::endl;break;
				case 2:mLog << "[DEBUG] "<< log.second << std::endl;std::cout << "[DEBUG] "<< log.second << std::endl;break;
				}
			}
		}
		//---------------------------------------------------------------------
	}
}