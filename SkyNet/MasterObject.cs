using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace SkyNet
{
    /// <summary>
    /// BOW DOWN TO THE ALMIGHTY GodInheritance OBJECT! :D
    /// </summary>
    public abstract class MasterObject
    {
        internal Dictionary<object, object> _inDict = new Dictionary<object, object>();
        public object this[object Key]
        {
            get
            {
                return _inDict.ContainsKey(Key) ? _inDict[Key] : null;
            }
            set
            {
                if (_inDict.ContainsKey(Key))
                    _inDict[Key] = value;
                else
                    _inDict.Add(Key, value);
            }
        }
    }
    public abstract class MasterObject<Key, Value>
    {
        internal Dictionary<Key, Value> _inDict = new Dictionary<Key, Value>();
        public Value this[Key Key]
        {
            get
            {
                return _inDict.ContainsKey(Key) ? _inDict[Key] : default(Value);
            }
            set
            {
                if (_inDict.ContainsKey(Key))
                    _inDict[Key] = value;
                else
                    _inDict.Add(Key, value);
            }
        }
    }
}
