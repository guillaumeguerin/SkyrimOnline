using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SkyNet.Math;

namespace SkyNet.SkyrimOnline.Game
{
    internal class Player
    {
        public uint GetRace
        {
            get
            {
                return _race;
            }
        }
        public uint GetLevel
        {
            get
            {
                return _level;
            }
        }
        public uint GetSex      //Could make this boolean
        {
            get
            {
                return _sex;
            }
        }
        public bool HasMount
        {
            get
            {
                return _mount != null;
            }
        }
        public Mount Mount
        {
            get
            {
                return _mount;
            }
            set
            {
                if (_mount != null)
                    if (_mount._baseID == value._baseID)
                        return;
                _mount = value;
            }
        }
        internal Mount _mount;
        internal Vector3 _position, _rotation;
        internal uint _race, _level, _sex;
        internal float _elapsed;
    }
}
