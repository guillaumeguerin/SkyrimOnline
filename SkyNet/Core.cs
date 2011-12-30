using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SkyNet
{
    public static class Core
    {
        static ulong _userID;
        static object _userIDLock;
        static List<UserData> _userData = new List<UserData>();

        public static UserData GetUser(ulong Data)
        {
            try
            {
                return _userData.First<UserData>((u) => Data == u._id);
            }
            catch
            {
                return null;
            }
        }

        public static ulong NextID(bool Increment=false)
        {
            ulong r = _userID;
            lock (_userIDLock)
            {
                if (Increment)
                    _userID++;
            }
            return r;
        }

        static Core()
        {
                _userData.Add(new UserData()
                {
                    _gold = 500,
                    _id = NextID(true)
                });
            
        }

        public static bool UserCanAfford(ulong User, uint Amount)
        {
            UserData a = GetUser(User);
            return a == null ?  false : a._gold >= Amount;
        }
        public static bool UserCharge(ulong User, uint Amount, bool Check = false)
        {
            UserData a = GetUser(User);
            if (a == null || a._gold < Amount)
                return false;
            a._gold -= Amount;
            return true;
        }
    }
}
