#include <iostream>
#include <netdb.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define SERVER_EXIT '#'
#define DEF_PORT 1601
#define SERVER_IP "127.0.0.1"
#define BUFFERSIZE 1024




bool is_client_connected(const char* msg);

int main() {
  int client;
  struct sockaddr_in server_adres; 
  client = socket(AF_INET, SOCK_STREAM, 0);
  if (client < 0) {
    std::cout<< "Error socket not created";
  }

  server_adres.sin_addr.s_addr = htons(INADDR_ANY);
  server_adres.sin_family = AF_INET;
  inet_pton(AF_INET, SERVER_IP, &server_adres.sin_addr);
  server_adres.sin_port = htons(DEF_PORT);
  std::cout<<"Client socket created";
  int connect_cl = connect(client, reinterpret_cast<sockaddr*>(&server_adres), sizeof(server_adres));
  if (connect_cl == 0) {
    std::cout<<"connected to server"<<inet_ntoa(server_adres.sin_addr)<<"with port number:"<<DEF_PORT<<std::endl;
  }
  char buffer[BUFFERSIZE];
  std::cout<<"Waiting for connection..."<<std::endl;
  recv(client, buffer, BUFFERSIZE,0);
  std::cout<<"connected"<<" "<<"Enter"<<SERVER_EXIT<<"to disconnect"<<std::endl;

  while (true)
  {
    std::cout<<"Client:";
    std::cin.getline(buffer, BUFFERSIZE);
    send(client, buffer, BUFFERSIZE, 0);
    if (is_client_connected(buffer)) {
      break;
    }
    std::cout<<"Server:";
    recv(client, buffer, BUFFERSIZE, 0);
    std::cout<<buffer;
    if (is_client_connected(buffer)) {
      break;
    }
    std::cout<<std::endl;
  }
  close(client);
  std::cout<<"disconnected"<<std::endl;
}

bool is_client_connected(const char* msg) {
  for(int i = 0; i < strlen(msg); ++i) {
      if(msg[i] == SERVER_EXIT) {
        return true;
      }
  }
  return false;
}
