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
    int client;
    int portNum  = 1500;
    bool is_exit = false;
    int buffsize = 1024;
    char buffer[buffsize];
    char* ip ="127.0.0.1";

    struct sockaddr_in server_addr;
    client = socket(AF_INET6, SOCK_STREAM, 0);

    if (client < 0) {
        std::cout<<"Error socket ..."<<std::endl;
        exit(1); 
    }

    std::cout<<"socket is created"<<std::endl;

    server_addr.sin_family = AF_INET6;
    server_addr.sin_port = htons(portNum);

    if (connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr))==0) {
        std::cout<<"connection port num:"<<portNum<<std::endl;
    }

    std::cout<<"accepting on server..."<<std::endl;
    recv(client, buffer, buffsize, 0);
    std::cout<<"connection confirmed"<<std::endl;

    std::cout<<"Enter to send massege"<<std::endl;

    do {
        std::cout<<"Client: ";
        do {
            std::cin>> buffer;
            send(client, buffer, buffsize, 0);
            if (*buffer == '\r') {
                send(client, buffer, buffsize, 0);
                *buffer = '*';
                is_exit = true;
            }
        }while(*buffer != 42);
        std::cout<<"server:";
        do {
            recv(client, buffer, buffsize, 0);
            std::cout<<buffer<<" ";
            if (*buffer == '\r') {
                *buffer = '*';
                is_exit = true;
            }
        }while(*buffer != 42);
            std::cout<<std::endl;
    }while(!is_exit);

    close(client);
    
    
    return 0;

}