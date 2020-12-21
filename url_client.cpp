#include "url_client.h"
#include <exception>
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>

void receive(URLClient &client)
{
    char buffer[MAX_DATA_LENGTH];

    while( client.has_more_data() )
    {
        std::cout << "I am here" << std::endl;
        memset(buffer, 0, sizeof(buffer));
        client >> buffer;
        std::cout << buffer << std::endl;
    }
}

int main( int agc, char *argv[])
{
    try
    {
        URLClient client =  URLClient(argv[1], atoi(argv[2]) );
        std::thread client_thread(receive, std::ref(client));
        client << "GET index.html\n";

        client_thread.join();
    }
    catch(std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}