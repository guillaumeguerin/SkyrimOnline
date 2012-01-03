using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SkyNet.Economy.Auctions;

namespace SkyNet
{
    public static class API
    {
        static ulong
            _userID,
            _auctionID;
        static object
            _userIDLock = (byte)0,
            _auctionIDLock = (byte)0;

        //May consider changing to Dictionary<int, [type]>
        static List<UserData> _userData = new List<UserData>();
        static List<AuctionEntry> _auctionData = new List<AuctionEntry>();

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

        public static ulong NextUserID(bool Increment=false)
        {
            ulong r = _userID;
            lock (_userIDLock)
            {
                if (Increment)
                    _userID++;
            }
            return r;
        }

        public static ulong NextAuctionID(bool Increment = false)
        {
            ulong r = _auctionID;
            lock (_auctionIDLock)
            {
                if (Increment)
                    _auctionID++;
            }
            return r;
        }

        /*internal*/
        static/* void _*/API()
        {
            _userData.Add(new UserData()
            {
                _gold = 500,
                _id = NextUserID(true)
            });
            _auctionData.AddRange(new[]
            {
                new AuctionEntry(0, 500, 250),
                 new AuctionEntry(0, 655),
                  new AuctionEntry(0, 200),
                  new AuctionEntry(0, 700),
                new AuctionEntry(1, 500)

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

        public static AuctionEntry[] GetAuctionsMatching(string String)
        {
            if (String[String.Length - 1] == ':')
                String = String.Remove(String.Length - 1);
            String = String.Replace(" ", "");
            string[] sp = String.Split(':');
            AuctionEntry[] d = _auctionData.ToArray();

            var a = 
                from auction in d
                where auction.Compare(sp)
                select auction;

            return a.ToArray();
        }
        public static ulong[] GetAuctionIDsMatching(string String)
        {
            if (String[String.Length - 1] == ':')
                String = String.Remove(String.Length - 1);
            String = String.Replace(" ", "");
            string[] sp = String.Split(':');
            AuctionEntry[] d = _auctionData.ToArray();

            var a =
                from auction in d
                where auction.Compare(sp)
                select auction._id;

            return a.ToArray();
        }
    }
}
