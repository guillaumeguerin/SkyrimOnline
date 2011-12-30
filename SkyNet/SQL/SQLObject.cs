using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MySql.Data.MySqlClient;
namespace SkyNet.SQL
{
    public interface SQLObject
    {
        void DoSQL(MySqlConnection Connection);
    }
}
