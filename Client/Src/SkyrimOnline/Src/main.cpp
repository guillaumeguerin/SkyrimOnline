/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include <Mod.h>
#include "Hipolipolopigus.h"
__declspec(dllexport) void main()
{
	//std::ostringstream os;
	//for(int i = 0; i < 6; ++i)
	//	os << Actor::Item
	//Log::GetInstance()->Debug(os.str());
	CLR_Init();
	srand((unsigned int)time(NULL));
	PrintNote("To play Skyrim Online, press F3");

	bool onlineMod = false;
	while(!SkyrimOnline::Mod::Exists())
	{
		if(GetKeyPressed(VK_F3))
		{
			onlineMod = true;
			break;
		}
		Wait(0);
	}

	if(onlineMod || SkyrimOnline::Mod::Exists())
		SkyrimOnline::Mod::GetInstance().Run();
}