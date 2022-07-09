// ServerApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ServerCore.h"

int main()
{
    ServerCore server;
    std::cout << "Successfully created a server!";
    server.Listen();
}
