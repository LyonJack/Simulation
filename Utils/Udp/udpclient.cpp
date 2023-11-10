#include "udpclient.h"
#include <iostream>

namespace simulation
{
    namespace utils
    {
        namespace udp
        {
            udp_client::udp_client()
            {
                WSAStartup(MAKEWORD(2, 2), &wsaData);
                clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

            }
            udp_client::~udp_client()
            {
                closesocket(clientSocket);
                WSACleanup();
            }
            void udp_client::setSockAddr(const char* destAddr, const int destPort)
            {
                clientSockAddr.sin_family = AF_INET;
                clientSockAddr.sin_port = htons(destPort);
                clientSockAddr.sin_addr.s_addr = inet_addr(destAddr);

            }
            void udp_client::sendData(const char* buf, const int len) const
            {
                sendto(clientSocket, buf, len, 0, (SOCKADDR*)&clientSockAddr, sizeof(clientSockAddr));
            }
        }
    }
}