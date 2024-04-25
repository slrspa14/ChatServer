using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
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

namespace file_send
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public TcpClient client = new TcpClient();//연결소켓
        public Stream stream;
        public MainWindow()
        {
            InitializeComponent();
        }

        public long File_size(string file_path)
        {
            return new FileInfo(file_path).Length;
        }
        private void send_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                client.Connect("10.10.20.113", 9195);
                if (client.Connected)
                {
                    MessageBox.Show("연결");
                    stream = client.GetStream();
                    byte[] size = new byte[4];
                    FileStream file = new FileStream("test.MP4", FileMode.Open, FileAccess.Read);
                    int file_size = (int)file.Length;
                    size = Encoding.Default.GetBytes(file_size.ToString());
                    stream.Write(size, 0, size.Length);
                    byte[] image = new byte[file_size];
                    stream.Write(image, 0, image.Length);
                }
                else
                    MessageBox.Show("접속 실패");
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
