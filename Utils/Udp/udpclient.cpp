#include "udpclient.h"
#include <string>
#include <cstring>
#include <cstdlib>
#include <thread>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#define RECV_BUFF_SIZE 1024
namespace simulation
{
    namespace utils
    {
        namespace udp
        {

            class UdpSocketClient::Impl
            {
            public:
                Impl(const std::string& serverIp, int serverPort)
                    : serverIp_(serverIp)
                    , serverPort_(serverPort)
                {

                }

                ~Impl()
                {
                    close();
                }

                bool connect()
                {
#ifdef _WIN32
                    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
                    {
                        std::cerr << "Failed to initialize WSA." << std::endl;
                        return false;
                    }
#endif
                    serverSocket_ = socket(AF_INET, SOCK_DGRAM, 0);
                    if (serverSocket_ == INVALID_SOCKET)
                    {
                        std::cerr << "Failed to create socket." << std::endl;
                        WSACleanup();
                        return false;
                    }

                    memset(&serverAddr_, 0, sizeof(serverAddr_));
                    serverAddr_.sin_family = AF_INET;
                    serverAddr_.sin_port = htons(serverPort_);
                    serverAddr_.sin_addr.s_addr = inet_addr(serverIp_.c_str());

                    if (::bind(serverSocket_, (struct sockaddr*)&serverAddr_, sizeof(serverAddr_)) == SOCKET_ERROR)
                    {
                        std::cerr << "Failed to bind socket." << std::endl;
                        closesocket(serverSocket_);
                        WSACleanup();
                        return false;
                    }

                    return true;
                }

                void close()
                {
                    if (serverSocket_ != INVALID_SOCKET)
                    {
#ifdef _WIN32
                        closesocket(serverSocket_);
                        WSACleanup();
#else
                        close(serverSocket_);
#endif
                        serverSocket_ = INVALID_SOCKET;
                    }
                }

                bool send(const std::string& data)
                {
                    if (serverSocket_ == INVALID_SOCKET)
                    {
                        std::cerr << "Not connected to the server." << std::endl;
                        return false;
                    }

                    int bytesSent = ::send(serverSocket_, data.c_str(), data.length(), 0);
                    if (bytesSent == -1)
                    {
                        std::cerr << "Error sending data." << std::endl;
                        return false;
                    }

                    return true;
                }

                bool sendToClient(const std::string& data, const std::string& strIp, int nPort)
                {
                    struct sockaddr_in destAddr {};
                    destAddr.sin_family = AF_INET;
                    destAddr.sin_port = htons(nPort);
                    destAddr.sin_addr.s_addr = inet_addr(strIp.c_str());

                    int size = sendto(serverSocket_, data.c_str(), data.length(), 0, (struct sockaddr*)&destAddr, sizeof(destAddr));

                    if (size == -1)
                    {
                        std::cerr << "Failed to send data." << std::endl;
                    }
                    return size != -1;
                }

                std::string receive()
                {
                    if (serverSocket_ == INVALID_SOCKET)
                    {
                        std::cerr << "Not connected to the server." << std::endl;
                        return "";
                    }

                    char buffer[RECV_BUFF_SIZE];
                    int addrLen = sizeof(clientAddr_);
                    int bytesRead = recvfrom(serverSocket_, buffer, RECV_BUFF_SIZE, 0, (struct sockaddr*)&clientAddr_, &addrLen);
                    if (bytesRead == -1)
                    {
                        std::cerr << "Error receiving data." << std::endl;
                        return "";
                    }

                    return std::string(buffer, bytesRead);
                }

                void startListening()
                {
                    listeningThread_ = std::thread([this]()
                        {
                            while (true)
                            {
                                std::string response = receive();
                                if (!response.empty())
                                {
                                    std::cout << "Received: " << response << std::endl;
                                    if (messageReceivedCallback_)
                                    {
                                        messageReceivedCallback_(response);
                                    }
                                }
                            }
                        });
                }

                void stopListening()
                {
                    if (listeningThread_.joinable())
                    {
                        listeningThread_.join();
                    }
                }


                void setReceivedCallback(MessageReceivedCallback callback)
                {
                    messageReceivedCallback_ = callback;
                }

            private:
                std::string serverIp_;
                int serverPort_;
                SOCKET serverSocket_;
#ifdef _WIN32
                WSADATA wsaData;
#endif
                struct sockaddr_in serverAddr_;
                struct sockaddr_in clientAddr_;
                std::thread listeningThread_;
                MessageReceivedCallback messageReceivedCallback_;
            };

            UdpSocketClient::UdpSocketClient(const std::string& serverIp, int serverPort)
                :m_pImpl(std::make_shared<UdpSocketClient::Impl>(serverIp, serverPort))
            {

            }

            UdpSocketClient::~UdpSocketClient()
            {
                m_pImpl->close();
            }

            bool UdpSocketClient::connect()
            {
                return m_pImpl->connect();
            }

            void UdpSocketClient::close()
            {
                return m_pImpl->close();
            }

            bool UdpSocketClient::send(const std::string& data)
            {
                return m_pImpl->send(data);
            }

            bool UdpSocketClient::sendToClient(const std::string& data, const std::string& strIp, int nPort)
            {
                return m_pImpl->sendToClient(data, strIp, nPort);
            }

            std::string UdpSocketClient::receive()
            {
                return m_pImpl->receive();
            }

            void UdpSocketClient::startListening()
            {
                return m_pImpl->startListening();
            }

            void UdpSocketClient::stopListening()
            {
                return m_pImpl->stopListening();
            }

            void UdpSocketClient::setReceivedCallback(MessageReceivedCallback callback)
            {
                return m_pImpl->setReceivedCallback(callback);
            }
        }
    }
}
