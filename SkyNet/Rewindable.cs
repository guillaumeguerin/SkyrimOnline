using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SkyNet
{
    /// <summary>
    /// One of my magical ideas ;) May look at step-rewinding (Not too hard to implement)
    /// </summary>
    public class Rewindable<T>
    {
        internal T _original,
            _current;
        public static implicit operator T(Rewindable<T> Value)
        {
            return Value._current;
        }
        public static implicit operator Rewindable<T>(T Value)
        {
            return new Rewindable<T>(Value);
        }
        internal Rewindable(T Value)
        {
            _original = _current = Value;
        }
        internal Rewindable<T> _rewind()
        {
            _current = _original;
            return this;
        }
        public T Current
        {
            get { return _current; }
        }
        public T Original
        {
            get { return _original; }
        }
    }
    public class RewindableString : Rewindable<string>
    {
        internal const string 
            _keyCurrent = "%c",
            _keyOriginal = "%o";
        public static implicit operator string(RewindableString Value)
        {
            return Value._current;
        }
        public static implicit operator RewindableString(string Value)
        {
            return new RewindableString(Value);
        }
        internal RewindableString(string Value)
            : base(Value)
        {
            
        }

        public RewindableString Rewind()
        {
            return (RewindableString)_rewind();
        }
        public RewindableString Append(string String)
        {
            _original += String;
            return this;
        }
        public RewindableString Format(string FormatString, object[] Arguments)
        {
            StringBuilder builder = new StringBuilder();
            if(Arguments==null)
                Arguments = new object[0];
            builder.AppendFormat(
                FormatString.Replace(_keyCurrent, _current).Replace(_keyOriginal, _original),
                Arguments);
            _current = builder.ToString();
            return this;
        }
        public RewindableString Replace(string Target, string New)
        {
            _current = _current.Replace(Target, New);
            return this;
        }

        public override string ToString()
        {
            return _current;
        }
    }
}
