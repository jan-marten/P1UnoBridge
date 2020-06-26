using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Net;      //required
using System.Net.Sockets;    //required

using System.Runtime;

namespace SimpleTcpServer
{
    class Program
    {
        // To execute; View -> Terminal --> dotnet run

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World! I am listening on port 9999 now...");

            TcpListener server = new TcpListener(IPAddress.Any, 9999);  
           // we set our IP address as server's address, and we also set the port: 9999

            server.Start();  // this will start the server

            while (true)   //we wait for a connection
            {
                TcpClient client = server.AcceptTcpClient();  //if a connection exists, the server will accept it

                NetworkStream ns = client.GetStream(); //networkstream is used to send/receive messages

                // byte[] hello = new byte[100];   //any message must be serialized (converted to byte array)
                // hello = Encoding.Default.GetBytes("hello world");  //conversion string => byte array

                // ns.Write(hello, 0, hello.Length);     //sending the message

                while (client.Connected)  //while the client is connected, we look for incoming messages
                {
                    byte[] msg = new byte[1024];     //the messages arrive as byte array
                    var readBytes = ns.Read(msg, 0, msg.Length);   //the same networkstream reads the message sent by the client

                    if (readBytes == 0)
                    {
                        ns.Close();
                        ns.Dispose();
                        ns = null;
                        client.Close();
                        client.Dispose();
                        client = null;

                        Console.WriteLine("Client disconnected.");
                        break;
                    }
                    else
                    {
                        Console.WriteLine($"Data received ({readBytes}/{msg.Length}): {BitConvertString(msg)}: {Encoding.Default.GetString(msg).Trim((char)0)}");
                    }
                }
            }
        }

        private static string BitConvertString(byte[] msg)
        {
            int zeroIndex = msg.Length;
            for (int i = 0; i < msg.Length; i++){
                if (msg[i] == 0){
                    zeroIndex = i;
                    break;
                }
            }

            return BitConverter.ToString(msg, 0, zeroIndex);
        }
    }
}
