using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace client
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    /// 

    static class Defined2
    {
        public const String Logout_Request = "00001000";
        public const String Get_Room_Request = "00001001";
        public const String Get_PlayersInRoom = "00001010";
        public const String Join_Room_Request = "00001011";
        public const String Create_Room_Request = "00001100";
    }

    public partial class RoomMenu : Window
    {
        public String roomId = "";
        public NetworkStream clientStream;

        public RoomMenu(NetworkStream clientStream1, String username)
        {
            InitializeComponent();
            clientStream = clientStream1;
            lblLoggedAs.Content = "Logged as: " + username;
        }

        public static byte[] ConvertToByteArray(string str, Encoding encoding)
        {
            return encoding.GetBytes(str);
        }

        public static String ToBinary(Byte[] data)
        {
            return string.Join("", data.Select(byt => Convert.ToString(byt, 2).PadLeft(8, '0')));
        }

        public static string BinaryToString(string data)
        {
            List<Byte> byteList = new List<Byte>();

            for (int i = 0; i < data.Length; i += 8)
            {
                byteList.Add(Convert.ToByte(data.Substring(i, 8), 2));
            }
            return Encoding.ASCII.GetString(byteList.ToArray());
        }

        public static string BinaryToString2(string data)
        {
            List<Byte> byteList = new List<Byte>();

            for (int i = 0; i < data.Length; i += 9)
            {
                byteList.Add(Convert.ToByte(data.Substring(i, 8), 2));
            }
            return Encoding.ASCII.GetString(byteList.ToArray());
        }

        public static String LogoutDesirializer(String str)
        {
            for (int i = 0; i < 2; i++)
            {
                str = str.Remove(0, str.IndexOf("$") + 1);
            }
            return str;
        }

        public static Dictionary<String, String[]> GetAllRoomsDesirializer(String str)
        {
            for (int i = 0; i < 2; i++)
            {
                str = str.Remove(0, str.IndexOf("$") + 1);
            }

            Dictionary<String, String[]> result = new Dictionary<String, String[]>();

            if (str.Contains("$"))
            {
                String[] rooms = str.Split("$");
                for (int i = 0; i < rooms.Length; i++)
                {
                    String[] temp = rooms[i].Split("*");
                    temp[1] = BinaryToString(temp[1]);
                    result.Add(temp[0], temp);
                }
            }
            else if (str == "00000000")
            {
                return result;
            }
            else
            {
                String[] temp = str.Split("*");
                temp[1] = BinaryToString(temp[1]);
                result.Add(temp[0], temp);
            } 

            return result;
        }

        public static String[] GetAllPlayersDesirializer(String str)
        {
            for (int i = 0; i < 2; i++)
            {
                str = str.Remove(0, str.IndexOf("$") + 1);
            }

            String[] players = str.Split("$");
            for (int i = 0; i < players.Length; i++)
            {                        
                players[i] = BinaryToString(players[i]);
            }

            return players;
        }

        public static String JoinRoomDesirializer(String str)
        {
            for (int i = 0; i < 2; i++)
            {
                str = str.Remove(0, str.IndexOf("$") + 1);
            }
            return str;
        }

        public static String CreateRoomDesirializer(String str)
        {
            for (int i = 0; i < 2; i++)
            {
                str = str.Remove(0, str.IndexOf("$") + 1);
            }
            return str;
        }

        public static String GetPlayersSerializer(String roomId)
        {
            String result = "";

            result += Defined2.Get_PlayersInRoom + "$";

            String temp = "";

            temp += roomId;

            result += ToBinary(ConvertToByteArray((temp.Length).ToString(), Encoding.ASCII)) + "$" + temp;

            return result;
        }

        public static String GetRoomsSerializer()
        { 
            return Defined2.Get_Room_Request;
        }

        private void btCreateRoom_Click(object sender, RoutedEventArgs e)
        {
            btBack2.Visibility = Visibility.Collapsed;
            btCreateRoom.Visibility = Visibility.Collapsed;
            btLogRoom.Visibility = Visibility.Collapsed;

            btnMaxPlayersDown.Visibility = Visibility.Visible;
            btnMaxPlayersUp.Visibility = Visibility.Visible;
            btnQcountDown.Visibility = Visibility.Visible;
            btnQcountUp.Visibility = Visibility.Visible;
            btnQtimeDown.Visibility = Visibility.Visible;
            btnQtimeUp.Visibility = Visibility.Visible;

            btnBack.Visibility = Visibility.Visible;
            btnConfirm.Visibility = Visibility.Visible;
            lblMaxPlayers.Visibility = Visibility.Visible;
            lblMaxPlayersNum.Visibility = Visibility.Visible;
            lblQtime.Visibility = Visibility.Visible;
            lblQuestionTime.Visibility = Visibility.Visible;
            lblQcountNum.Visibility = Visibility.Visible;
            lblQcount.Visibility = Visibility.Visible;
            tbRoomName.Visibility = Visibility.Visible;
        }

        private void btBack2_Click(object sender, RoutedEventArgs e)
        {
            // New menu
            // Need to serialize the logout of the user
            var mainWindow = new MainWindow();
            mainWindow.Show();
            this.Close();
        }

        private void btnConfirm_Click(object sender, RoutedEventArgs e)
        {
            String name = tbRoomName.Text;
            String maxPlayers = (String)lblMaxPlayersNum.Content;
            String maxQtime = (String)lblQtime.Content;
            String QcountNum = (String)lblQcountNum.Content;

            String result = "";

            result += Defined2.Create_Room_Request + "$";

            String temp = "";

            temp += ToBinary(ConvertToByteArray(name, Encoding.ASCII)) + "$";
            temp += maxPlayers + "$";
            temp += maxQtime + "$";
            temp += QcountNum;

            result += ToBinary(ConvertToByteArray((temp.Length).ToString(), Encoding.ASCII)) + "$" + temp;

            byte[] buffer;
            buffer = new byte[4096];

            buffer = new ASCIIEncoding().GetBytes(result);

            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();         

            buffer = new byte[4096];
            int bytesRead = clientStream.Read(buffer, 0, 4096);
            String id = Encoding.ASCII.GetString(buffer, 0, bytesRead);
            id = CreateRoomDesirializer(id);
            roomId = id;

            result = GetPlayersSerializer(id);

            buffer = new byte[4096];
            buffer = new ASCIIEncoding().GetBytes(result);
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();

            buffer = new byte[4096];
            bytesRead = clientStream.Read(buffer, 0, 4096);
            id = Encoding.ASCII.GetString(buffer, 0, bytesRead);
            String[] allPlayers = GetAllPlayersDesirializer(id);
            lblServer.Content = String.Join(" ", allPlayers);

            //while (true)
            //{
            //    Thread.Sleep(3000);

            //    buffer = new byte[4096];
            //    buffer = new ASCIIEncoding().GetBytes(result);
            //    clientStream.Write(buffer, 0, buffer.Length);
            //    clientStream.Flush();

            //    buffer = new byte[4096];
            //    bytesRead = clientStream.Read(buffer, 0, 4096);
            //    id = Encoding.ASCII.GetString(buffer, 0, bytesRead);
            //    id = CreateRoomDesirializer(id);
            //    lblServer.Content = id;
            //}
        }

        private void btLogRoom_Click(object sender, RoutedEventArgs e)
        {
            String result = GetRoomsSerializer();

            byte[] buffer;
            buffer = new byte[4096];

            buffer = new ASCIIEncoding().GetBytes(result);

            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();

            buffer = new byte[4096];
            int bytesRead = clientStream.Read(buffer, 0, 4096);
            String id = Encoding.ASCII.GetString(buffer, 0, bytesRead);
            Dictionary<String, String[]> allRooms = GetAllRoomsDesirializer(id);

            if (allRooms.Count() > 0)
            {
                btCreateRoom.Visibility = Visibility.Collapsed;
                btLogRoom.Visibility = Visibility.Collapsed;
                lblLoggedAs.Margin = new Thickness(400,316,0,0);
            }

            String temp = "";

            foreach (var item in allRooms)
            {
                temp += "ID: " + item.Value[0] + " | " + "Name: " + item.Value[1] + " | " + "Question answer time: " + item.Value[2] + 
                    " | " + "Max players count: " + item.Value[3] + " | " +  "Question count: " + item.Value[4] + "\n";
            }

            lblServer.Content = temp;
        }

        private void btnBack_Click(object sender, RoutedEventArgs e)
        {
            btBack2.Visibility = Visibility.Visible;
            btCreateRoom.Visibility = Visibility.Visible;
            btLogRoom.Visibility = Visibility.Visible;

            btnMaxPlayersDown.Visibility = Visibility.Collapsed;
            btnMaxPlayersUp.Visibility = Visibility.Collapsed;
            btnQcountDown.Visibility = Visibility.Collapsed;
            btnQcountUp.Visibility = Visibility.Collapsed;
            btnQtimeDown.Visibility = Visibility.Collapsed;
            btnQtimeUp.Visibility = Visibility.Collapsed;

            btnBack.Visibility = Visibility.Collapsed;
            btnConfirm.Visibility = Visibility.Collapsed;
            lblMaxPlayers.Visibility = Visibility.Collapsed;
            lblMaxPlayersNum.Visibility = Visibility.Collapsed;
            lblQtime.Visibility = Visibility.Collapsed;
            lblQuestionTime.Visibility = Visibility.Collapsed;
            lblQcountNum.Visibility = Visibility.Collapsed;
            lblQcount.Visibility = Visibility.Collapsed;
            tbRoomName.Visibility = Visibility.Collapsed;
        }

        private void btnQtimeDown_Click(object sender, RoutedEventArgs e)
        {
            lblQtime.Content = "" + (int.Parse((string)lblQtime.Content) - 1);
        }

        private void btnQtimeUp_Click(object sender, RoutedEventArgs e)
        {
            lblQtime.Content = "" + (int.Parse((string)lblQtime.Content) + 1);
        }

        private void btnMaxPlayersDown_Click(object sender, RoutedEventArgs e)
        {
            lblMaxPlayersNum.Content = "" + (int.Parse((string)lblMaxPlayersNum.Content) - 1);
        }

        private void btnMaxPlayersUp_Click(object sender, RoutedEventArgs e)
        {
            lblMaxPlayersNum.Content = "" + (int.Parse((string)lblMaxPlayersNum.Content) + 1);
        }

        private void btnQcountDown_Click(object sender, RoutedEventArgs e)
        {
            lblQcountNum.Content = "" + (int.Parse((string)lblQcountNum.Content) - 1);
        }

        private void btnQcountUp_Click(object sender, RoutedEventArgs e)
        {
            lblQcountNum.Content = "" + (int.Parse((string)lblQcountNum.Content) + 1);
        }

        private void btnRefresh_Click(object sender, RoutedEventArgs e)
        {
            String result = GetPlayersSerializer(roomId);
            byte[] buffer;
            buffer = new byte[4096];
            buffer = new ASCIIEncoding().GetBytes(result);
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();

            buffer = new byte[4096];
            int bytesRead = clientStream.Read(buffer, 0, 4096);
            String id = Encoding.ASCII.GetString(buffer, 0, bytesRead);
            String[] allPlayers = GetAllPlayersDesirializer(id);
            lblServer.Content = String.Join(" ", allPlayers);
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            String result = "hello";
            byte[] buffer;
            buffer = new byte[4096];

            buffer = new ASCIIEncoding().GetBytes(result);

            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
        }
    }
}
