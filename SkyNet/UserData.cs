using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MySql.Data.MySqlClient;

namespace SkyNet
{
    public class UserData:SQL.SQLObject
    {
        internal ulong
            _id;
        internal uint
            _gold;

        public void DoSQL(MySqlConnection Connection)
        {

        }
    }
}
