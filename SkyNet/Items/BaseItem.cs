using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SkyNet.Items
{
    public class BaseItem:MasterObject
    {
        internal uint
            _gameID,             //The in-game BaseID, not the RefID
            _value;              //Value in Gold
        internal ulong
            _id;                 //The Server-side ID
        public virtual Values.Type_Item Type
        {
            get
            {
                return Values.Type_Item.Base;
            }
        }
    }
}
