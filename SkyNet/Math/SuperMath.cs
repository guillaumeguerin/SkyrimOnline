using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SkyNet.Math
{
    public static class SuperMath
    {
        public static double Nearest(double Value, double[] Array)
        {
            int n = 0;
            double
                lastDifference,
                difference = 0;
            int i = 0,
                l = Array.Length;
            for (; i < l; i++)
            {
                lastDifference = difference;
                difference = Value - Array[i];
                if (difference < 0)
                    difference = -difference;
                if (difference < lastDifference)
                    n = i;
            }
            return Array[n];
        }
        public static int NearestIndex(double Value, double[] Array)
        {
            int n = 0;
            double
                lastDifference,
                difference = 0;
            int i = 0,
                l = Array.Length;
            for (; i < l; i++)
            {
                lastDifference = difference;
                difference = Value - Array[i];
                if (difference < 0)
                    difference = -difference;
                if (difference < lastDifference)
                    n = i;
            }
            return n;
        }
    }
}
