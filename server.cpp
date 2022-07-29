#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

int main() {
    int client, server;
    int portNum = 1500;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];

    struct sockaddr_in server_addr;
    socklen_t size;

    client = socket(AF_INET6, SOCK_STREAM, 0);

    if (client < 0) {
        std::cout<<"Error socket ..."<<std::endl;
        exit(1); 
    }

    std::cout<<"socket is created"<<std::endl;

    server_addr.sin_family = AF_INET6;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    if ((bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0) {
        std::cout<<"Error binding connection"<<std::endl;
        return -1;
    } 

    size = sizeof(server_addr);
    std::cout<<"Looking clients"<<std::endl;
    listen(client, 1);

    int client_count = 1;
    server = accept(client, (struct sockaddr*)&server_addr, &size);

    if (server < 0) {
        std::cout<<"Error on accepting"<<std::endl;
    } 

    while(server > 0) {
        strcpy(buffer, "server connected...\n");
        send(server, buffer, bufsize, 0);
        std::cout<<"connecting with client "<<client_count <<std::endl;
        std::cout<<"Enter to end connection"<<std::endl;

        std::cout<<"client:";
        do {
            recv(server, buffer, bufsize, 0);
            std::cout<<buffer<<" ";
            if (*buffer == '\r') {
                *buffer = '*';
                isExit = true;

            }
        }while(*buffer != '*');

        do {
            std::cout<<"\nServer: ";
            do {
                std::cin>>buffer;
                send(server, buffer, bufsize, 0);
                if (*buffer =='\r') {
                    send(server, buffer, bufsize, 0);
                    *buffer = '*';
                    isExit = true;
                }
            }while(*buffer != '*');
            std::cout<<"Client: ";
            do {
                recv(server, buffer, bufsize, 0);
                std::cout<< buffer << " ";
                if (*buffer == '\r') {
                    *buffer = '*';
                    isExit = true;
                }
            }while(*buffer != '*');
        }while(!isExit);

        close(server);
        std::cout<<"GOODBYE..";
        isExit = false;
        exit(1);
    }

    close(client);
    return 0;
}
