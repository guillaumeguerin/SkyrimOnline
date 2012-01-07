using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MySql.Data.MySqlClient;
namespace SkyNet.SQL
{
    public interface SQLObject
    {
        void Read(MySqlConnection Connection);
        void Write(MySqlConnection Connection);
        bool Compare(string[] Comparisson);
    }
}
