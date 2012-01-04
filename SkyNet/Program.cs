using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SkyNet;
using SkyNet.Economy.Auctions;

namespace SkyNet
{
    public class Program
    {
        internal static void Main(string[] args)
        {
            API._auctionData.Add(new AuctionEntry(0,0,0,4));
            AuctionEntry[] a = API.GetAuctionsMatching("rt=4");
        }
    }
}
