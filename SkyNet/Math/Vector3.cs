using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace SkyNet.Math
{
    [ComVisible(true)]
    [Guid("C55B6F57-FA02-43F0-93E2-14DA834A218B")]
    public class Vector3
    {
        public float
            X,
            Y,
            Z;
        public float[] ToArray
        {
            get
            {
                return new[] { X, Y, Z };
            }
        }
        public Vector3(float X, float Y, float Z)
        {
            this.X = X;
            this.Y = Y;
            this.Z = Z;
        }
        public override string ToString()
        {
            return string.Format("[[0],[1],[2]]", X, Y, Z);
        }
    }
}
