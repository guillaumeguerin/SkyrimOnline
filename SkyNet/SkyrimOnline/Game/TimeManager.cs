using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SkyNet.SkyrimOnline.Game
{
    public class TimeManager
    {
        private uint
            _month,
            _day;
            
        private float 
            _scale,
            _hour;

        /// <summary>
        /// Could make this readonly, though customization could be fun ;D
        /// </summary>
        internal static int[] DayPerMonth =
		{
			31,28,31,30,31,30,31,31,30,31,30,31
		};

        //Could remove backings here, though unsure of performance implications on Update(...)
        public uint Day
        {
            get
            {
                return _day;
            }
            set
            {
                _day = value;
            }
        }
        public uint Month
        {
            get
            {
                return _month;
            }
            set
            {
                _month = value;
            }
        }
        public float Hour
        {
            get
            {
                return _hour;
            }
            set
            {
                _hour = value;
            }
        }
        public float Scale
        {
            get
            {
                return _scale;
            }
            set
            {
                _scale = value;
            }
        }

        public void Update(float Elapsed)
        {
            _hour += (Elapsed / 3600.0f) * _scale;
            if (_hour > 24)
            {
                _hour = 0;
                ++_day;         //Micro-optimization over _day++
                if (_day > DayPerMonth[_month])
                {
                    _day = 0;
                    _month++;
                    if (_month == DayPerMonth.Length)
                        _month = 0;
                }
            }
        }
    }
}
