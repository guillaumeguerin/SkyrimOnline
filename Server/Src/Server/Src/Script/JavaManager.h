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