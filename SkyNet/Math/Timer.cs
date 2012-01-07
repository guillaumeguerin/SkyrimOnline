using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace SkyNet.Math
{
    public class Timer
    {
        long _startTime = Environment.TickCount;
        public float Elapsed
        {
            get
            {
                return (Environment.TickCount - _startTime) / 10000000.0f; //10000000 = TimeSpan.TicksPerSecond
            }
        }
        public float ElapsedAndRestart
        {
            get
            {
                float r = (Environment.TickCount - _startTime) / 10000000.0f;
                _startTime = Environment.TickCount;
                return r;
            }
        }
    }
}
