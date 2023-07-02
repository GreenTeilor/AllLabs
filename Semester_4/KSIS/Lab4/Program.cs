using MailKit;
using MailKit.Net.Imap;
using MailKit.Search;
using MimeKit;
using Org.BouncyCastle.Asn1;
using System;
using System.IO;
using System.Net;
using System.Net.Security;
using System.Net.Sockets;
using System.Reflection.PortableExecutable;
using System.Security.Cryptography;
using System.Text;

namespace Laba_4
{
    internal class Program
    {
        static string ReadResponse(SslStream stream)
        {
            int bytesRead;
            byte[] buffer = new byte[256];
            string response = "";
            while ((bytesRead = stream.Read(buffer, 0, buffer.Length)) > 0)
            {
                response += Encoding.ASCII.GetString(buffer, 0, bytesRead);
                if (response.EndsWith("\r\n"))
                    break;
            }
            return response;
        }
        static string HiddenRead()
        {
            string result = "";
            while (true)
            {
                ConsoleKeyInfo key = Console.ReadKey(true);
                if (result.Length > 0 && key.Key == ConsoleKey.Backspace)
                    result = result.Remove(result.Length - 1);
                else if (key.Key == ConsoleKey.Enter)
                    break;
                else 
                    result += key.KeyChar;
            }
            return result;
        }
        static void PrintHeader(MimeMessage message, int index)
        {
            Console.WriteLine($"Message {index}");
            for (int j = 0; j < 20; j++)
                Console.Write("-");
            Console.WriteLine();
            Console.WriteLine("Date: {0}", message.Date);
            Console.WriteLine("From: {0}", message.From);
            Console.WriteLine("Subject: {0}", message.Subject);
            Console.WriteLine("To: {0}", message.To);
            Console.WriteLine();
        }
        static void PrintBody(MimeMessage message)
        {
            Console.WriteLine("Date: {0}", message.Date);
            Console.WriteLine("From: {0}", message.From);
            Console.WriteLine("Subject: {0}", message.Subject);
            Console.WriteLine("To: {0}", message.To);
            Console.WriteLine();
            Console.WriteLine(message.GetTextBody(MimeKit.Text.TextFormat.Plain));
            Console.WriteLine();
            Console.WriteLine();
        }
        static void Main(string[] args)
        {
            int port = 993;
            string host = "imap.gmail.com";
            string? query, response;
            byte[] buffer = new byte[256];
            int tag = 1;

            SslStream? stream = null;
            TcpClient? client = null;

            try
            {
                client = new TcpClient(host, port);
                stream = new SslStream(client.GetStream(), false);
                stream.AuthenticateAsClient("imap.gmail.com");

                response = ReadResponse(stream);
                Console.WriteLine(response);

                string? mail = null, password = null;
                while (true)
                {
                    try
                    {
                        Console.Write("Input comand: ");
                        query = Convert.ToString(tag++, 16) + " ";
                        query += Console.ReadLine()?.Trim();

                        if (mail != null && query.ToLower().Contains("fetch"))
                        { 
                            using (var imapClient = new ImapClient())
                            {
                                imapClient.Connect(host, port, true);
                                imapClient.Authenticate(mail, password);

                                string[] queryArgs = query.Split(' ');
                                Console.Write("Input mailbox: ");
                                string? mailBox = Console.ReadLine();

                                var folder = imapClient.GetFolder(mailBox);
                                folder.Open(FolderAccess.ReadOnly);
                                var imapQuery = SearchQuery.All;
                                var uids = folder.Search(imapQuery);

                                int begin, end;
                                if (queryArgs[3].ToLower().Equals("all"))
                                {
                                    begin = 1;
                                    end = uids.Count;
                                }
                                else if (queryArgs[3].Split(':').Length > 1)
                                {
                                    string[] bounds = queryArgs[3].Split(':');
                                    begin = Int32.Parse(bounds[0]);
                                    end = Int32.Parse(bounds[1]);
                                    if (begin <= 0 || end > uids.Count)
                                    {
                                        Console.WriteLine("BAD BOUNDS");
                                        continue;
                                    }
                                }
                                else
                                {
                                    begin = end = Int32.Parse(queryArgs[3]);
                                }

                                if (queryArgs[2].ToLower().Equals("header"))
                                {
                                    for (int i = begin; i <= end; i++)
                                    {
                                        var message = folder.GetMessage(uids[i - 1]);
                                        PrintHeader(message, i);
                                    }
                                }
                                else if (queryArgs[2].ToLower().Equals("body"))
                                {
                                    for (int i = begin; i <= end; i++)
                                    {
                                        var message = folder.GetMessage(uids[i - 1]);
                                        PrintBody(message);
                                    }
                                }
                                imapClient.Disconnect(true);
                            }
                            
                        }
                        else
                        {
                            if (query.ToLower().Contains("authenticate") || query.ToLower().Contains("login"))
                            {
                                Console.Write("Input mail address: ");
                                mail = Console.ReadLine();
                                Console.Write("Input password: ");
                                password = HiddenRead();
                                Console.WriteLine();

                                if (query.ToLower().Contains("authenticate"))
                                {
                                    string plainArg = '\0' + mail + '\0' + password;
                                    string base64Arg = Convert.ToBase64String(Encoding.ASCII.GetBytes(plainArg));
                                    query += " " + base64Arg;
                                }
                                else
                                {
                                    query += " " + mail + " " + password;
                                }
                            }
                            
                            query += "\r\n";
                            buffer = Encoding.ASCII.GetBytes(query);
                            stream.Write(buffer);
                            Console.Write(ReadResponse(stream));

                            if (query.ToLower().Contains("logout\r\n"))
                                break;
                        }
                    }
                    catch (SocketException ex)
                    {
                        Console.WriteLine(ex.ToString());
                        stream?.Close();
                        client?.Close();
                        client = new TcpClient(host, port);
                        stream = new SslStream(client.GetStream(), false);
                        stream.AuthenticateAsClient("imap.gmail.com");
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
            finally
            {
                stream?.Close();
                client?.Close();
            }
        }
    }
}