#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main() {
    int client, server;
    int portnum = 1500;
    bool isExit = false;
    int buffsize = 1024;
    char buffer[buffsize];

    struct sockaddr_in server_addr;
    socklen_t size;
    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) {
        std::cout << "Erorr connection";
        exit(1);
    }
    std::cout << "socket server connection created..."<<std::endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portnum);

    if ((bind(client,(struct sockaddr*) & server_addr, sizeof(server_addr))) < 0) {
        std::cout<< "=> Error binding connection"<<std::endl;
        return -1;
    }

    size = sizeof(server_addr);
    std::cout<<"looking for clients..."<<std::endl;
    listen(client, 1);

    int client_count = 1;
    server = accept(client, (struct sockaddr* )&server_addr, &size);
    if (server < 0)
    {
        std::cout<<"Error on accepting..."<<std::endl;
    }

    while (server > 0) {
        strcpy(buffer, "=> server connected...\n");
        send(server, buffer, buffsize, 0);
        std::cout << "=> Connected with the client #" << client_count << ", you are good to go..." <<std::endl;
        std::cout << "\n=> Enter # to end the connection\n" << std::endl;
    }
    
    std::cout<<"client: ";
    do {
        recv(server, buffer, buffsize, 0);
        std::cout<<buffer<<" ";
        if (*buffer == '#') {
            *buffer = '*';
            isExit = true;

        }
    }while(*buffer != '*');

        do {
           std::cout << "\nServer: ";
            do {
                std::cin >> buffer;
                send(server, buffer, buffsize, 0);
                if (*buffer == '#') {
                    send(server, buffer, buffsize, 0);
                    *buffer = '*';
                    isExit = true;
                }
            } while (*buffer != '*');

            std::cout << "Client: ";
            do {
                recv(server, buffer, buffsize, 0);
                std::cout << buffer << " ";
                if (*buffer == '#') {
                    *buffer == '*';
                    isExit = true;
                }
            } while (*buffer != '*');
        } while (!isExit);


    return 0;
}