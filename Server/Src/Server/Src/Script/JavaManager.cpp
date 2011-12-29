#include "stdafx.h"
#include <Script/JavaManager.h>

#include <jni.h>

#ifdef _WIN32
#define SEP_REPERTOIRE ';'
#else
#define SEP_REPERTOIRE ':'
#endif

#define NULL_CHECK0(e) if ((e) == 0) return 0

namespace Skyrim
{
    namespace Script
    {
        //---------------------------------------------------------------------------------------
        void JavaManager::CreateJvm(JavaManager::ClassPath path) {
                JavaVMInitArgs args;
                JavaVMOption options[1];

                std::string lPath = "-Djava.class.path=";
                for(int i = 0; i < path.size(); i++)
                        lPath += path[i] + SEP_REPERTOIRE;

                /* There is a new JNI_VERSION_1_4, but it doesn't add anything for the purposes of our example. */
                args.version = JNI_VERSION_1_6;
                args.nOptions = 1;
                options[0].optionString = (char*)lPath.c_str();
                args.options = options;
                args.ignoreUnrecognized = JNI_FALSE;

                JNI_CreateJavaVM(&mJvm, (void **)&mEnv, &args);
        }
        //---------------------------------------------------------------------------------------
        void JavaManager::DestroyJvm()
        {
                //DestroyJavaVM(mJvm);
        }
        //---------------------------------------------------------------------------------------
        jstring JavaManager::GetMainClassName(char *jarname)
        {
#define MAIN_CLASS "Main-Class"

                jclass cls;
                jmethodID mid;
                jobject jar, man, attr;
                jstring str, result = 0;

                NULL_CHECK0(cls = mEnv->FindClass("java/util/jar/JarFile"));
                NULL_CHECK0(mid = mEnv->GetMethodID(cls, "<init>",
                        "(Ljava/lang/String;)V"));
                NULL_CHECK0(str = NewPlatformString(jarname));
                NULL_CHECK0(jar = mEnv->NewObject(cls, mid, str));
                NULL_CHECK0(mid = mEnv->GetMethodID(cls, "getManifest",
                        "()Ljava/util/jar/Manifest;"));
                man = mEnv->CallObjectMethod(jar, mid);
                if (man != 0) {
                        NULL_CHECK0(mid = mEnv->GetMethodID(
                                mEnv->GetObjectClass( man),
                                "getMainAttributes",
                                "()Ljava/util/jar/Attributes;"));
                        attr = mEnv->CallObjectMethod( man, mid);
                        if (attr != 0) {
                                NULL_CHECK0(mid =mEnv->GetMethodID(
                                        mEnv->GetObjectClass(attr),
                                        "getValue",
                                        "(Ljava/lang/String;)Ljava/lang/String;"));
                                NULL_CHECK0(str = NewPlatformString( MAIN_CLASS));
                                result = (jstring)mEnv->CallObjectMethod( attr, mid, str);
                        }
                }
                return result;
        }
        //---------------------------------------------------------------------------------------
        jstring JavaManager::getPlatformEncoding() {
                if (mEncoding == NULL) {
                        jstring propname = mEnv->NewStringUTF("sun.jnu.encoding");
                        if (propname) {
                                jclass cls;
                                jmethodID mid;
                                NULL_CHECK0 (cls = mEnv->FindClass("java/lang/System"));
                                NULL_CHECK0 (mid = mEnv->GetStaticMethodID(
                                        cls,
                                        "getProperty",
                                        "(Ljava/lang/String;)Ljava/lang/String;"));
                                mEncoding = (jstring)mEnv->CallStaticObjectMethod (
                                        cls, mid, propname);
                        }
                }
                return mEncoding;
        }
        //---------------------------------------------------------------------------------------
        jboolean JavaManager::isEncodingSupported(jstring enc) {
                jclass cls;
                jmethodID mid;
                NULL_CHECK0 (cls = mEnv->FindClass("java/nio/charset/Charset"));
                NULL_CHECK0 (mid = mEnv->GetStaticMethodID(cls,
                        "isSupported",
                        "(Ljava/lang/String;)Z"));
                return mEnv->CallStaticBooleanMethod( cls, mid, enc);
        }
        //---------------------------------------------------------------------------------------
        jstring JavaManager::NewPlatformString(char *s)
        {
                int len = (int)strlen(s);
                jclass cls;
                jmethodID mid;
                jbyteArray ary;
                jstring enc;

                if (s == NULL)
                return 0;
                enc = getPlatformEncoding();

                ary = mEnv->NewByteArray( len);
                if (ary != 0) {
                        jstring str = 0;
                mEnv->SetByteArrayRegion( ary, 0, len, (jbyte *)s);
                if (!mEnv->ExceptionOccurred()) {
                                if (isEncodingSupported(enc) == JNI_TRUE) {
                                        NULL_CHECK0(cls = mEnv->FindClass("java/lang/String"));
                                        NULL_CHECK0(mid = mEnv->GetMethodID(cls, "<init>",
                                                    "([BLjava/lang/String;)V"));
                                str = (jstring)mEnv->NewObject(cls, mid, ary, enc);
                        } else {
                                        /*If the encoding specified in sun.jnu.encoding is not
                                            endorsed by "Charset.isSupported" we have to fall back
                                            to use String(byte[]) explicitly here without specifying
                                            the encoding name, in which the StringCoding class will
                                            pickup the iso-8859-1 as the fallback converter for us.
                                */
                                        NULL_CHECK0(cls = mEnv->FindClass( "java/lang/String"));
                                        NULL_CHECK0(mid = mEnv->GetMethodID( cls, "<init>",
                                                    "([B)V"));
                                str = (jstring)mEnv->NewObject( cls, mid, ary);
                                }
                        mEnv->DeleteLocalRef(ary);
                        return str;
                        }
                }
                return 0;
        }
        //---------------------------------------------------------------------------------------
        JNIEnv* JavaManager::GetJNI()
        {
                return mEnv;
        }
        //---------------------------------------------------------------------------------------
        JavaManager::JavaManager(JavaManager::ClassPath path)
                :mEncoding(nullptr)
        {
                CreateJvm(path);
        }
        //---------------------------------------------------------------------------------------
    }
}