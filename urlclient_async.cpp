#include "url_client.h"
#include <exception>
#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <future>

void receive(URLClient &client)
{
    char buffer[MAX_DATA_LENGTH];

    while( client.has_more_data() )
    {
        try
        {
            memset(buffer, 0, sizeof(buffer));
            client >> buffer;
            std::cout << buffer << std::endl;
        }
        catch (std::exception &ex)
        {
            std::cout << ex.what() << std::endl;
            return;
        }
    }
}

void send_packet(URLClient &client)
{
    std::string line;
    
    while(true)
    {
        try
        {
            std::getline(std::cin, line);
            if (line == "quit")
            {
                break;
            }
            client << line.c_str();
            client << "\r\n";
        }
        catch (std::exception &ex)
        {
            std::cout<<ex.what()<<std::endl;
            return;
        }
    }

}

int main( int agc, char *argv[])
{
    try
    {
        URLClient client =  URLClient(argv[1], atoi(argv[2]) );
        auto recvRet = std::async(std::launch::async,receive,std::ref(client));
        auto sendRet = std::async(std::launch::async,send_packet,std::ref(client));
        recvRet.wait();
        sendRet.wait();
    }
    catch(std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}