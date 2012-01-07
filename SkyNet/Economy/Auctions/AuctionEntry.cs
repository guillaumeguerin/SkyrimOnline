using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MySql.Data.MySqlClient;
using SkyNet.Math;

namespace SkyNet.Economy.Auctions
{
    public class AuctionEntry:SQL.SQLObject
    {
        internal static double[] PresetTimes = 
        {
            0.5,
            1,
            2,
            4,
            6,
            12,
            24,
            48
        };
        internal ulong
            _id,
            _auctioner,
            _highBidder,
            _listedInstance,
            _time;
        internal uint
            _buyout,
            _minBid,
            _currentBid;
        internal bool
            _closed;

        public object Get(string Value)
        {
            switch (Value)
            {
                case "id": return _id;
                case "au": return _auctioner;
                case "hi": return _highBidder;
                case "bu": return _buyout;
                case "mi": return _minBid;
                case "cu": return _currentBid;
                default: return _id + ":" + _auctioner + ":"  + _highBidder+ ":" + _buyout+":" + _minBid + ":" + _currentBid;
            }
        }

        public AuctionEntry(ulong Auctioner, ulong Instance, uint Buyout, byte Time, uint MinBid = 0)
        {
            _auctioner = Auctioner;
            _buyout = Buyout;
            _listedInstance = Instance;
            _time = (ulong)DateTime.Now.Add(TimeSpan.FromHours(PresetTimes[Time])).Ticks;
            _minBid = _currentBid = MinBid;
        }
        public void Write(MySqlConnection Connection)
        {

        }
        public void Read(MySqlConnection Connection)
        {

        }
        public bool Compare(string[] Comparisson)
        {
            try
            {
                for (int i = 0; i < Comparisson.Length; i++)
                    if (!iCompare(Comparisson[i]))
                        return false;
                return true;
            }
            catch
            {
                return false;
            }
        }
        public bool TimeCheck(ulong CurrentTime, bool Close = true)
        {
            bool r;
            if (r = ((CurrentTime >= _time) && Close))
                _closed = true;
            return r;
        }
        internal bool iCompare(string s)
        {
            if (s == string.Empty)
                return false;
            if (s.Contains('!'))
            {
                string[] b = s.Split('!');
                if (b.Length != 2)
                    return false;
                switch (b[0])
                {
                    case "a":
                        return ulong.Parse(b[1]) != _auctioner;
                    case "bo":
                        return ulong.Parse(b[1]) != _buyout;
                    case "cb":
                        return ulong.Parse(b[1]) != _currentBid;
                    case "cl":
                        return _closed != (b[1] == "1");
                    case "hb":
                        return ulong.Parse(b[1]) != _highBidder;
                    case "id":
                        return ulong.Parse(b[1]) != _id;
                    case "ii":
                        return ulong.Parse(b[1]) != _listedInstance;
                    case "mb":
                        return ulong.Parse(b[1]) != _minBid;
                    case "rt":
                        {
                            TimeSpan remaining = new TimeSpan((long)_time - DateTime.Now.Ticks);
                            return byte.Parse(b[1]) != SuperMath.NearestIndex(remaining.Hours + (remaining.Minutes / (double)60), PresetTimes);
                        }
                    case "ti":
                            return ulong.Parse(b[1]) != _time;
                }
            }
            else if (s.Contains('='))
            {
                string[] b = s.Split('=');
                if (b.Length != 2)
                    return false;
                switch (b[0])
                {
                    case "a":
                        return ulong.Parse(b[1]) == _auctioner;
                    case "bo":
                        return ulong.Parse(b[1]) == _buyout;
                    case "cb":
                        return ulong.Parse(b[1]) == _currentBid;
                    case "cl":
                        return _closed == (b[1] == "1");
                    case "hb":
                        return ulong.Parse(b[1]) == _highBidder;
                    case "id":
                        return ulong.Parse(b[1]) == _id;
                    case "ii": 
                        return ulong.Parse(b[1]) == _listedInstance;
                    case "mb":
                        return ulong.Parse(b[1]) == _minBid;
                    case "rt":
                        {
                            TimeSpan remaining = new TimeSpan((long)_time - DateTime.Now.Ticks);
                            return byte.Parse(b[1]) == SuperMath.NearestIndex(remaining.Hours + (remaining.Minutes / (double)60), PresetTimes);
                        }
                    case "ti":
                            return ulong.Parse(b[1]) == _time;
                }
            }
            else if (s.Contains('>'))
            {
                string[] b = s.Split('>');
                if (b.Length != 2)
                    return false;
                switch (b[0])
                {
                    case "a":
                        return ulong.Parse(b[1]) < _auctioner;
                    case "bo":
                        return ulong.Parse(b[1]) < _buyout;
                    case "cb":
                        return ulong.Parse(b[1]) < _currentBid;
                    case "cl":
                        return _closed;
                    case "hb":
                        return ulong.Parse(b[1]) < _highBidder;
                    case "id":
                        return ulong.Parse(b[1]) < _id;
                    case "ii":
                        return ulong.Parse(b[1]) < _listedInstance;
                    case "mb":
                        return ulong.Parse(b[1]) < _minBid;
                    case "rt":
                        {
                            TimeSpan remaining = new TimeSpan((long)_time - DateTime.Now.Ticks);
                            return byte.Parse(b[1]) < SuperMath.NearestIndex(remaining.Hours + (remaining.Minutes / (double)60), PresetTimes);
                        }
                    case "ti":
                            return ulong.Parse(b[1]) < _time;
                }
            }
            else if (s.Contains('<'))
            {
                string[] b = s.Split('<');
                if (b.Length != 2)
                    return false;
                switch (b[0])
                {
                    case "a":
                        return ulong.Parse(b[1]) > _auctioner;
                    case "bo":
                        return ulong.Parse(b[1]) > _buyout;
                    case "cb":
                        return ulong.Parse(b[1]) > _currentBid;
                    case "cl":
                        return !_closed;
                    case "hb":
                        return ulong.Parse(b[1]) > _highBidder;
                    case "id":
                        return ulong.Parse(b[1]) > _id;
                    case "ii":
                        return ulong.Parse(b[1]) > _listedInstance;
                    case "mb":
                        return ulong.Parse(b[1]) > _minBid;
                    case "rt":
                        {
                            TimeSpan remaining = new TimeSpan((long)_time - DateTime.Now.Ticks);
                            return byte.Parse(b[1]) > SuperMath.NearestIndex(remaining.Hours + (remaining.Minutes / (double)60), PresetTimes);
                        }
                    case "ti":
                            return ulong.Parse(b[1]) > _time;
                }
            }
            return false;
        }
        public byte ProcessBid(uint BidAmount, ulong Bidder)
        {
            if (_closed)
                return 1;
            else if (Bidder == _highBidder)
                return 2;
            else if (BidAmount <= _currentBid)
                return 3;
            else if (BidAmount < _minBid)
                return 4;
            else if (Bidder == _auctioner)
                return 5;
            else if (!API.UserCanAfford(Bidder, BidAmount))
                return 6;
            _minBid = BidAmount + 10;
            _currentBid = BidAmount;
            _highBidder = Bidder;
            return 0;
        }
        public byte ProcessBuyout(ulong Buyer)
        {
            if (!API.UserCanAfford(Buyer, _buyout))
                return 1;

            return 0;
        }
        public void ProcessEnd()
        {

        }
    }
}
