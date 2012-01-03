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
            //Retrieve sample auction with Auctioneer ID 0 and a buyout greater than 200 and less than 700 and not equal to 655. The trailing ':' is purged to prevent errors
            AuctionEntry[] a = API.GetAuctionsMatching("a=0:bo>200:bo<700:bo!655:");
            ulong[] aIDMode = API.GetAuctionIDsMatching("a=0:bo>200:bo<700:bo!655:");
        }
    }
}
