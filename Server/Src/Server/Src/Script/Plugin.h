#pragma once

#include <Game/IWorld.h>

namespace Skyrim
{
	namespace Script
	{
		class Plugin
		{
		public:

			// If one plugin returns true then it will cancel the event !

			__declspec(nothrow) virtual void OnEnable() = 0;
			__declspec(nothrow) virtual void OnDisable() = 0;

			__declspec(nothrow) virtual void OnNewShard(Game::IWorld*) = 0;
		};
	}
}