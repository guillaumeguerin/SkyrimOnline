using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SkyNet.Economy.Auctions;
using System.Threading;
using SkyNet.Items;
using System.Diagnostics;
using SkyNet.SkyrimOnline.Game;
using SkyNet.SkyrimOnline.Network;

namespace SkyNet
{
    public delegate void AddShardHandler(Server S, World W);
    public delegate void UserLoginHandler(Server S, Session Session, UserData Data);
    public static class API
    {
        public static event AddShardHandler AddShard;
        public static event UserLoginHandler UserLogin;

        internal static void OnAddShard(Server S, World W)
        {
            AddShard(S, W);
        }
        internal static void OnUserLogin(Server S, Session Session, UserData Data)
        {
            UserLogin(S, Session, Data);
        }

        internal static Process
            _this;
        static ulong
            _userID,
            _auctionID;
        static object
            _userIDLock = (byte)0,
            _auctionIDLock = (byte)0;
        static readonly Thread
            _auctionCheck;
        static bool 
            _running = true;

        //May consider changing to Dictionary<ulong, [type]>
        internal static List<UserData> _userData = new List<UserData>();
        internal static List<AuctionEntry> _auctionData = new List<AuctionEntry>();
        internal static List<ItemInstance> _itemInstances = new List<ItemInstance>();

        public static Process This
        {
            get { return _this; }
        }

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

        static /*internal void _*/API()
        {
            _auctionCheck = new Thread(AuctionCheck);
            _auctionCheck.Start();
            _this = Process.GetCurrentProcess();
            AddShard += (w, o) => Console.WriteLine("World added: {0}", o._name);
            UserLogin += (s, sess, dat) => Console.WriteLine("User logged in: {0}", dat._name);
        }

        static void AuctionCheck()
        {
            AuctionEntry[] auctions;
            ulong now;
            while (_running)
            {
                now = (ulong)DateTime.Now.Ticks;
                auctions = _auctionData.ToArray();
                var a = from auction in auctions
                        where !auction._closed
                        where auction.TimeCheck(now)
                        select auction._id;
                if (!_running)
                { /*Shutdown cleanly*/ }
            }
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
        public static ItemInstance GetItemInstance(ulong ID)
        {
            var a = from item in _itemInstances
                    where item._id == ID
                    select item;
            return a.FirstOrDefault();
        }
    }
}
