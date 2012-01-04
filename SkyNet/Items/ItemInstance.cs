using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SkyNet.Items
{
    public class ItemInstance
    {
        internal ulong
            _id,            //The global ID of the item instance
            _creator,       //The creator of the item instance
            _base;          //The global ID of the BaseItem represented in this instance
    }
}
