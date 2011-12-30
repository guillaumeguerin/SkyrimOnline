using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MySql.Data.MySqlClient;

namespace SkyNet.Economy.Auctions
{
    public class AuctionEntry:SQL.SQLObject
    {
        ulong
            _id,
            _auctioner,
            _highBidder;
        uint
            _buyout,
            _minBid,
            _currentBid;
        internal bool
            _closed;

        public AuctionEntry(ulong Auctioner, uint Buyout, uint MinBid = 0)
        {
            _auctioner = Auctioner;
            _buyout = Buyout;
            _minBid = _currentBid = MinBid;
        }
        public void DoSQL(MySqlConnection Connection)
        {

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
            else if (!Core.UserCanAfford(Bidder, BidAmount))
                return 6;
            _currentBid = BidAmount;
            _highBidder = Bidder;
            return 0;
        }
        public byte ProcessBuyout(ulong Buyer)
        {
            if (!Core.UserCanAfford(Buyer, _buyout))
                return 1;

            return 0;
        }
    }
}
