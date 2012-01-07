using System;
using System.Collections.Generic;
using System.Linq;
using SkyNet.Math;

namespace SkyNet.SkyrimOnline.Game
{
    internal class Mount
    {
        internal uint _baseID;
        internal Vector3 _position, _rotation;
        public Mount(uint BaseID)
        {
            _baseID = BaseID;
        }
        public uint GetBaseID
        {
            get
            {
                return _baseID;
            }
        }
    }
}
