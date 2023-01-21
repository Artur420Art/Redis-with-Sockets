Socket programming is a means of communicating data between two computers across a network. Connections can be made using either a connection-oriented protocol or a connectionless protocol. In our case, we will use TCP/IP which is a connection-oriented protocol.
socket-programming!<br>
![p2p](https://user-images.githubusercontent.com/92685845/182643608-14803cdb-29ae-4418-bab6-bce661b83c5b.png)




<br>

Listening for a Connection

• A server (program) runs on a specific computer and has a socket that is bound to a specific port. The server waits and listens to the socket for a client to make a connection request. Screen Shot 2022-07-30 at 20 13 31<br>
![2](https://user-images.githubusercontent.com/92685845/182643903-6d8a9db5-9b95-41d4-9527-f295177fb8ce.png)

• If everything goes well, the server accepts the connection.

• Upon acceptance,the server gets a new socket bound to a different port. – It needs a new socket so that it can continue to listen to the original socket for connection requests while serving the connected client. Screen Shot 2022-07-30 at 20 29 37

Server-Side Sockets

• Bind socket to IPaddress/port int bind(int socket, struct sockaddr *addr, int addr_len)

• Mark the socket as accepting connections int listen(int socket, int backlog)

• “Passive open” accepts connect int accept(int socket, struct sockaddr *addr, int addr_len) (returns a new socket to talk to the client)

Client-Side Sockets

• int connect(int socket, struct sockaddr *addr, int addr_len)

How to use this program

First compile the server.cpp file

make Redis

./Redis

Then compile the client.cpp file.

make client

./client

When connection has created and everything is accepted, client can write his message and press enter to send massege.

When you want to end a connection you need to add # symbol, and then connection will be terminated.
