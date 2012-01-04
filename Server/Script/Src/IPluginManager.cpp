/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/
#include "stdafx.h"
#include "IPluginManager.h"
#include "PluginManagerJNI.h"
/*
 * Class:     com_skyrimonline_PluginManager
 * Method:    register
 * Signature: (JJI)V
 */
JNIEXPORT void JNICALL Java_com_skyrimonline_PluginManager_register
	(JNIEnv * env, jobject obj, jlong ptr, jlong pluginPtr, jint e)
{
	Skyrim::IPluginManager* plugin = (Skyrim::IPluginManager*)ptr;
	plugin->Register((void*)pluginPtr, e);
}

namespace Skyrim
{
	//---------------------------------------------------------------------
#pragma data_seg (".shared" )
	IPluginManager* IPluginManager::mInstance = nullptr;
#pragma data_seg ()
	//---------------------------------------------------------------------
}