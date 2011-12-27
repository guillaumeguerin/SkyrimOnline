using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.IO;
using System.CodeDom;
using System.CodeDom.Compiler;

namespace SkyNet.Extension
{
    public class SuperAssembly
    {
        static CodeDomProvider dom = CodeDomProvider.CreateProvider("csharp");
        static CompilerParameters domParams = new CompilerParameters(new[]
            {
                "SkyNet.dll"
            });
        static SuperAssembly()
        {
            domParams.GenerateExecutable = false;
            domParams.GenerateInMemory = true;
        }
        Dictionary<string, SuperClass> _classes = new Dictionary<string, SuperClass>();
        public Dictionary<string, SuperClass> Classes
        {
            get
            {
                Dictionary<string, SuperClass> r;
                lock (_classes)
                {   r = _classes;   }
                return r;
            }
        }
        public SuperClass this[string Name]
        {
            get
            {
                Dictionary<string, SuperClass> r;
                lock (_classes)
                {
                    r = _classes;
                }
                return r.ContainsKey(Name) ?
                    r[Name]
                    : null;
            }
            set
            {
                lock (_classes)
                {
                    if (_classes.ContainsKey(Name))
                        _classes[Name] = value;
                    else
                        _classes.Add(Name, value);
                }
            }
        }
        public Dictionary<string, CompilerResults> LoadAll()
        {
            string[] Files = Directory.GetFiles("./Code");
            Dictionary<string, CompilerResults> r = new Dictionary<string, CompilerResults>();
            CompilerResults _r = null;
            lock(_classes)
            {
                foreach (string s in Files)
                    r.Add(s, _r = Load(s));
            }
            return r;
        }
        public CompilerResults Load(string File)
        {
            CompilerResults res = dom.CompileAssemblyFromSource(domParams, new[] { File });
            if (!res.Errors.HasErrors)
            {
                Assembly a = res.CompiledAssembly;
                Type[] t = a.GetTypes();
                foreach (Type T in t)
                    this[T.FullName] = new SuperClass(T, a);
            }
            return res;
        }
        public SuperAssembly()
        {
            Assembly a = Assembly.GetCallingAssembly();
            Type[] t = a.GetTypes();
            foreach (Type T in t)
                this[T.FullName] = new SuperClass(T, a);
        }
        public object Call(string Name, object[] Parameters = null)
        {
            string[] p = Name.Split('.');
            string _class = "",
                _method = "";
            if (p.Length == 2)
            {
                _class = p[0];
                _method = p[1];
            }
            else if (p.Length > 3)
            {
                for (int i = 0; i < p.Length - 1; i++)
                    _class += p[i]+".";
                _class.Remove(_class.Length - 1);
                _method = p[p.Length - 1];
            }
            try
            {
                return this[_class][_method].Call(Parameters);
            }
            catch (System.Exception ex)
            {
                return null;
            }
        }
        public T Call<T>(string Name, object[] Parameters = null)
        {
            string[] p = Name.Split('.');
            string _class = "",
                _method = "";
            if (p.Length == 2)
            {
                _class = p[0];
                _method = p[1];
            }
            else if (p.Length >= 3)
            {
                for (int i = 0; i < p.Length - 1; i++)
                    _class += p[i] + ".";
                _class =_class.Remove(_class.Length - 1, 1);
                _method = p[p.Length - 1];
            }
            try
            {
                return this[_class][_method].Call<T>(Parameters);
            }
            catch (System.Exception ex)
            {
                object o = null;
                return (T)o;
            }
        }
    }
    public class SuperClass
    {
        Dictionary<string, SuperMethod> _methods = new Dictionary<string, SuperMethod>();
        public SuperMethod this[string Name]
        {
            get
            {
                return _methods.ContainsKey(Name) ?
                    _methods[Name]
                    : null;
            }
            set
            {
                if (_methods.ContainsKey(Name))
                    _methods[Name] = value;
                else
                    _methods.Add(Name, value);
            }
        }
        string _name,
            _fullName;
        object _reference;
        public string Name
        {
            get { return _name; }
        }
        public string FullName
        {
            get { return _fullName; }
        }
        public SuperClass(Type T, Assembly Parent)
        {
            MethodInfo[] m = T.GetMethods(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
            _reference = Parent.CreateInstance(_fullName = T.FullName);
            foreach (MethodInfo mi in m)
                _methods.Add(mi.Name, new SuperMethod(mi, _reference));
            _name = T.Name;
        }
    }
    public class SuperMethod
    {
        Type[] _parameters;
        Func<object[], object> _action;
        public SuperMethod(MethodInfo Method, object Parent)
        {
            ParameterInfo[] p;
            int l,
                i=0;
            _parameters = new Type[l = (p = Method.GetParameters()).Length];
            for (; i < l; i++)
                _parameters[i] = p[i].ParameterType;
            _action = (P) => Method.Invoke(Parent, P == null? new object[0] : P);
        }
        public object Call(object[] Parameters = null)
        {
            return _action(Parameters);
        }
        public T Call<T>(object[] Parameters = null)
        {
            return (T)Call(Parameters);
        }
    }
}
