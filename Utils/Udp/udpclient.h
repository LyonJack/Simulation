#pragma once
#include <cstdint>
#if _WIN32
#include<Winsock2.h>
#endif // _WIN32

namespace simulation
{
    namespace utils
    {
        namespace udp
        {
            class udp_client
            {
            public:
                udp_client();
                ~udp_client();
                void setSockAddr(const char* destAddr, const int destPort);
                void sendData(const char* buf, const int len) const;
            private:
                WSADATA wsaData;
                SOCKET clientSocket;
                sockaddr_in clientSockAddr;
            };
        }
    }
}
