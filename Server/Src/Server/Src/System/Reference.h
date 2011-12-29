#pragma once

namespace Skyrim
{
	namespace System
	{
		/**
		 * Holds reference count and manages the object's life
		 */
		class Reference
		{
		public:

			Reference()
				:mRefCount(1)
			{}

			virtual ~Reference()
			{
			}

			void Drop()
			{
				--mRefCount;
				if(mRefCount == 0)
				{
					delete this;
					return;
				}
			}

			void Acquire()
			{
				++mRefCount;
			}

		private:

			int32_t mRefCount;
		};
	}
}