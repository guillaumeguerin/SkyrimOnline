/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#pragma once

#include <System/Event.h>
#include <System/Reference.h>

namespace Skyrim{
	namespace System
	{
		struct EventListener :
			public virtual boost::enable_shared_from_this<EventListener>
		{
			typedef boost::shared_ptr<EventListener> pointer;

			EventListener(){}
			virtual ~EventListener(){}

			virtual void OnEvent(System::Event::pointer pEvent)
			{
				mEvents.push(pEvent);
			}
		protected:
			Concurrency::concurrent_queue<System::Event::pointer> mEvents;
		};
	}
}