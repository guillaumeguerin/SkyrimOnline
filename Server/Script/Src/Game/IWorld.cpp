/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include <Game/IWorld.h>
#include <Game/WorldJNI.h>

/*
 * Class:     com_skyrimonline_game_World
 * Method:    GetName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_skyrimonline_game_World_getName
  (JNIEnv * env, jobject obj, jlong ptr)
{
	if(ptr)
	{
		Skyrim::Game::IWorld* world = (Skyrim::Game::IWorld*)ptr;
		return env->NewStringUTF(world->GetName().c_str());
	}
	return env->NewStringUTF("null ptr");
}

/*
 * Class:     com_skyrimonline_game_World
 * Method:    Count
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_skyrimonline_game_World_count
  (JNIEnv * env, jobject obj, jlong ptr)
{
	Skyrim::Game::IWorld* world = (Skyrim::Game::IWorld*)ptr;
	return world->Count();
}