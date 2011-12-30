using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SkyNet.Entities
{
    public class NPC : BaseEntity
    {
        public override int Type
        {
            get
            {
                return Values.Type_Entity.NPC;
            }
        }
        public virtual int Type_NPC
        {
            get
            {
                return Values.Type_NPC.Base;
            }
        }
        public NPC(uint refID)
            : base(refID)
        {

        }
    }
}
