using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MySql.Data.MySqlClient;
using System.Diagnostics.Contracts;

namespace SkyNet
{
    public class UserData:SQL.SQLObject
    {
        internal ulong
            _id;
        internal uint
            _gold;
        internal string _name,
            _pass;
        /// <summary>
        /// For titles, etc
        /// </summary>
        internal RewindableString _friendlyName = "";

        public bool Compare(string[] Comparisson)
        {
            return true;
        }
        public void Write(MySqlConnection Connection)
        {

        }
        internal const string
            loadQueryFormat = "SELECT ID, user_pass, user_nicename, meta_value FROM wp_users WHERE user_login = [0]",
            loadAllQuery = "SELECT user_login, ID, user_pass, user_nicename, meta_value, gold FROM wp_users";
        public void Read(MySqlConnection Connection)
        {
            //The original load query is weird... Gonna have to ask about how the class functions. Here's mine for now :3
        }
        public static UserData[] LoadAll(MySqlConnection Connection)
        {
            Contract.Requires(Connection != null, "Connection is null.");
            MySqlDataReader reader = new MySqlCommand(loadAllQuery, Connection).ExecuteReader();
            List<UserData> r = new List<UserData>();
            object[] row = new object[5];
            int count;
            while (reader.Read())
            {
                count = reader.GetValues(row);
                r.Add(new UserData()
                    {
                        _name = (string)row[0],
                        _id = (ulong)row[1],
                        _pass = (string)row[2],
                        _friendlyName = (string)row[3],
                        _gold = (uint)row[5]
                    });
            }
            return r.ToArray();
        }
    }
}
