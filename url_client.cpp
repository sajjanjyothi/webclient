#include "url_client.h"
#include <exception>
#include <iostream>
#include <string>
#include <cstdlib>

int main( int agc, char *argv[])
{
    try
    {
        URLClient client =  URLClient(argv[1], atoi(argv[2]) );
        char buffer[1024];
        client << "GET index.html\n";
        // client << "PUT index.html\n";
        client >> buffer;
        std::cout << buffer << std::endl;
    }
    catch(std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}