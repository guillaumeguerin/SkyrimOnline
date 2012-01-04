/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#pragma once

#if defined SCRIPT_EXPORTS
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

namespace Skyrim
{
	namespace System
	{
		class DECLDIR Log
		{
		public:

			enum Level
			{
				NONE,
				LOW,
				VERBOSE
			};

			static Log* GetInstance();
			void Print(const std::string&);
			void Debug(const std::string&);
			void Error(const std::string&);

			void SetLevel(Level pLevel);

			void Update();

		private:

			void PrintTime();

			Log();

			Concurrency::concurrent_queue<std::pair<int, std::string>> mToLog;

			std::ofstream mLog;
			static Log* mInstance;
			Level mLevel;
		};
	}
}