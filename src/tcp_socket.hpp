#pragma once
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

namespace snr
{
#define MAX_BLACKLOG 512
    class TcpSocket
    {
    private:
        int sockfd = -1;
        int port;
        int family;
        int protocol;
        struct sockaddr_in addr;
        char clientIP[INET_ADDRSTRLEN] = "";
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

    public:
        int fd()
        {
            return this->sockfd;
        }

        int setSocket(bool isSync)
        {
            if (this->sockfd != -1)
            {
                return this->sockfd;
            }
            this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (this->sockfd == -1)
            {
                std::cout << "Error: init socket error" << std::endl;
                return -1;
            }
            if (isSync)
            {
                int flags = fcntl(sockfd, F_GETFL, 0);
                fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
            }
            return this->sockfd;
        }

        int bindSocket(int port)
        {
            this->addr.sin_family = AF_INET;
            this->addr.sin_port = htons(port);
            addr.sin_addr.s_addr = INADDR_ANY;
            if (bind(this->sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
            {
                std::cout << "Error: bind" << std::endl;
                return -1;
            }
            return 1;
        }

        int onListen()
        {
            if (listen(this->sockfd, MAX_BLACKLOG) == -1)
            {
                std::cout << "Error: bind" << std::endl;
                return -1;
            }
            return 1;
        }

        int onAccept()
        {
            int conn = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
            if (conn < 0)
            {
                std::cout << "Error: accept" << std::endl;
                return -1;
            }
            return conn;
        }

        struct sockaddr_in *getClientAddr()
        {
            return &(this->clientAddr);
        }

        void closeSocket()
        {
            close(sockfd);
        }
    };
};
