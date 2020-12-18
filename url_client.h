#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include "url_exception.h"


#define MAX_DATA_LENGTH 1024

class URLClient
{
    public:
        URLClient(const std::string &url, int port=80)
        {
            struct sockaddr_in   serv_addr = {0};
            struct hostent      *server;

            if ((_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            {
                throw URLException("Cannot create socket");
            }

            server = gethostbyname(url.c_str());
            if (server == NULL)
            {
               throw URLException("oops,I cannot get DNS record"); 
            }

            serv_addr.sin_family = AF_INET;
            bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
            serv_addr.sin_port = htons(port);

            if ( connect(_sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            {
                throw URLException("Cannot connect");
            }

        }
  
        int operator << (const char *data)
        {
            return write(_sock_fd,data,MAX_DATA_LENGTH);
        }

        int operator >> (char *data)
        {
            return read(_sock_fd, data, MAX_DATA_LENGTH);
        }

        ~URLClient()
        {
            if ( _sock_fd != -1)
            {
                close(_sock_fd);
                _sock_fd = -1;
            }
        }
    private:
        int _sock_fd;
};