using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net;
using System.Net.Sockets;


namespace client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    ///
    static class Defined
    {
        public const String LOGIN = "00000010";
        public const String SIGN_UP = "00000011";
        public const String ERROR = "00000001";
    }

    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
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

            for (int i = 0; i < data.Length; i += 9)
            {
                byteList.Add(Convert.ToByte(data.Substring(i, 8), 2));
            }
            return Encoding.ASCII.GetString(byteList.ToArray());
        }

        public static String LogSeserialize(String username, String password)
        {
            String result = Defined.LOGIN;
            result += "$";
            String usernameByte = ToBinary(ConvertToByteArray(username, Encoding.ASCII));
            String passwordByte = ToBinary(ConvertToByteArray(password, Encoding.ASCII));
            String helper = usernameByte + "$" + passwordByte;
            result += ToBinary(ConvertToByteArray((helper.Length).ToString(), Encoding.ASCII));
            result += "$";
            result += helper;
            return result;
        }
        public static String SignSeserialize(String username, String password, String email)
        {
            String result = Defined.SIGN_UP;
            result += "$";
            String usernameByte = ToBinary(ConvertToByteArray(username, Encoding.ASCII));
            String passwordByte = ToBinary(ConvertToByteArray(password, Encoding.ASCII));
            String emailByte = ToBinary(ConvertToByteArray(email, Encoding.ASCII));
            String helper = usernameByte + "$" + passwordByte + "$" + emailByte;
            result += ToBinary(ConvertToByteArray((helper.Length).ToString(), Encoding.ASCII));
            result += "$";
            result += helper;
            return result;
        }

        public static String LogDeserialize(String data)
        {
            for (int i = 0; i < 2; i++)
            {
                data = data.Remove(0, data.IndexOf("$") + 1);
            }
            return BinaryToString(data);
        }

        private void btLogin_Click(object sender, RoutedEventArgs e)
        {
            btLogin.Visibility = Visibility.Collapsed;
            btSignup.Visibility = Visibility.Collapsed;
            btExit.Visibility = Visibility.Collapsed;
            btConfirm.Visibility = Visibility.Visible;
            tbUsername.Visibility = Visibility.Visible;
            tbPassword.Visibility = Visibility.Visible;
        }

        private void btSignup_Click(object sender, RoutedEventArgs e)
        {
            btLogin.Visibility = Visibility.Collapsed;
            btSignup.Visibility = Visibility.Collapsed;
            btExit.Visibility = Visibility.Collapsed;
            btConfirm.Visibility = Visibility.Visible;
            tbUsername.Visibility = Visibility.Visible;
            tbPassword.Visibility = Visibility.Visible;
            tbEmail.Visibility = Visibility.Visible;
        }

        private void btExit_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }

        private void btConfirm_Click(object sender, RoutedEventArgs e)
        {
            TcpClient client = new TcpClient();

            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 666);

            client.Connect(serverEndPoint);

            NetworkStream clientStream = client.GetStream();

            String username = tbUsername.Text;
            String password = tbPassword.Text;
            String msg;

            byte[] buffer;

            buffer = new byte[4096];
            int bytesRead = clientStream.Read(buffer, 0, 4096);
            String id = Encoding.ASCII.GetString(buffer, 0, bytesRead);

            lblServer.Content = id;

            if (tbEmail.Visibility == Visibility.Visible) // Sign up
            {
                String email = tbEmail.Text;
                msg = SignSeserialize(username, password, email);
            }
            else // Login
            {
                msg = LogSeserialize(username, password);
            }

            buffer = new ASCIIEncoding().GetBytes(msg);

            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();

            buffer = new byte[4096];
            bytesRead = clientStream.Read(buffer, 0, 4096);
            id = Encoding.ASCII.GetString(buffer, 0, bytesRead);
            id = LogDeserialize(id);
            lblServer.Content = id;

            if (id == "Logged in successfully")
            {
                // New menu
                var roomMenu = new RoomMenu(clientStream, username);
                roomMenu.Show();
                this.Close();
            }
        }
    }
}
