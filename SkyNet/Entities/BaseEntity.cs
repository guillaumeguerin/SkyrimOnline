using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using SkyNet.Math;

namespace SkyNet.Entities
{
    [ComVisible(true)]
    [Guid("EBD8FF69-8951-4AD2-BCDF-5AA489B899EB")]
    public class BaseEntity
    {
        uint _ref;
        public BaseEntity(uint RefID)
        {
            _ref = RefID;
        }
        public Vector3 Position;
        public virtual int Type
        {
            get
            {
                return Values.Type_Entity.Base;   //Base
            }
        }
    }
}
