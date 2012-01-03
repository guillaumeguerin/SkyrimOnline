using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SkyNet.Items
{
    public class BaseItem:MasterObject
    {
        internal uint 
            gameID,             //The in-game BaseID, not the RefID
            value;              //Value in Gold
        internal ulong
            creator;            //Creator of the item, 0 for items created by the world
        public virtual Values.Type_Item Type
        {
            get
            {
                return Values.Type_Item.Base;
            }
        }
    }
}
