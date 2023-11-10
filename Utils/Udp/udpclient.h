#pragma once
#include <iostream>
#include <memory>
#include <functional>

namespace simulation
{
    namespace utils
    {
        namespace udp
        {
            typedef std::function<void(const std::string& message)> MessageReceivedCallback;

            class UdpSocketClient
            {
            public:
                UdpSocketClient(const std::string& serverIp, int serverPort);
                ~UdpSocketClient();

            public:
                bool connect();

                void close();

                bool send(const std::string& data);

                bool sendToClient(const std::string& data, const std::string& strIp, int nPort);

                std::string receive();

                void startListening();

                void stopListening();

                void setReceivedCallback(MessageReceivedCallback callback);

            private:
                class Impl;
                std::shared_ptr<Impl> m_pImpl;
            };
        }
    }
}
