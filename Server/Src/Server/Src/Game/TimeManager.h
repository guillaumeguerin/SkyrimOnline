/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#pragma once

namespace Skyrim
{
	namespace Game
	{
		class TimeManager
		{
		public:

			TimeManager();

			void SetHour(float pHour);
			void SetDay(float pDay);
			void SetMonth(float pMonth);

			float GetHour();
			float GetDay();
			float GetMonth();

			void Update(float pElapsed);

		private:

			static int DayPerMonth[12];

			float mHour;
			float mDay;
			float mMonth;
			float mTimeScale;
		};
	}
}