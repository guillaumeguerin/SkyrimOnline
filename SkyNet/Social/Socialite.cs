using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SkyNet.Social
{
    public class Socialite:MasterObject
    {
        internal ulong 
            _socialID,
            _userID;
        List<uint> _achievements = new List<uint>();
        public Socialite()
        {

        }
    }
}
