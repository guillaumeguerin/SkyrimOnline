using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MySql.Data.MySqlClient;

namespace SkyNet.Social
{
    public class Achievement : SQL.SQLObject
    {
        internal uint _id;
        internal byte _points;
        internal string _name;
        public void Write(MySqlConnection Connection)
        {

        }
        public void Read(MySqlConnection Connection)
        {

        }
        public bool Compare(string[] Comparisson)
        {
            return false;
        }
    }
}
