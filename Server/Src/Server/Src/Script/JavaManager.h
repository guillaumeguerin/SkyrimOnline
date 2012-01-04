/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#pragma once

#include <jni.h>

namespace Skyrim
{
    namespace Script
    {
        /**
        * @class JavaManager
        * @brief Manage Java's VM
        */
        class JavaManager {
		public:

			typedef std::vector<std::string> ClassPath;

			JavaManager(ClassPath path);

			void CreateJvm(ClassPath path);
			void DestroyJvm();

			JNIEnv* GetJNI();

			jstring GetMainClassName(char *jarname);
			jstring NewPlatformString(char *s);
			jstring getPlatformEncoding();
			jboolean isEncodingSupported(jstring enc);

		private:

			JavaVM* mJvm;
			JNIEnv* mEnv;
			jstring mEncoding;
        };
    }
}