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
        IntPtr _ref;
        public BaseEntity(IntPtr RefID)
        {
            _ref = RefID;
        }
        public Vector3 Position
        {
            get
            {
                return (Vector3)Core.Call("GetPosition", _ref);
            }
            set
            {
                Core.Call("SetPosition", value.ToArray);
            }
        }
    }
}
