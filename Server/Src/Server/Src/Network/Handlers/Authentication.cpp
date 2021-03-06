/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include <Network/Session.h>
#include <Network/Server.h>
#include <DAO/Account.h>

namespace Skyrim
{
	namespace Network
	{
		//---------------------------------------------------------------------
		void Session::HandleAuth(Packet& pData)
		{
			if(mAccount.Id == 0)
			{
				mAccount.User = pData.String(0);
				mAccount.Pass = pData.String(1);

				auto dao = DAO::Load(mAccount);
				dao->Add(shared_from_this());
				dao->userData = LOAD_USER;
				mServer->GetDatabaseWorkQueue()->Push(dao);
			}
		}
		//---------------------------------------------------------------------
		void Session::HandleUserLoad()
		{
			if(mAccount.Id != 0)
			{
				mAuth = true;
				GetServer().SendShardList(shared_from_this());
			}
			else
			{
				Close();
			}
		}
		//---------------------------------------------------------------------
		void Session::HandleShardPick(Packet& pData)
		{
			if(mAccount.Id != 0)
				GetServer().MoveToWorld(pData.String(0), shared_from_this());
		}
		//---------------------------------------------------------------------
	}
}