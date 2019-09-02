README 

This code emulates a simple TCP Echo Server and Client.

All code was written in C++ using socket programming. Two functions were coded, "readline" and "written" which handled reading to the client/server and writing to the client/server respectively. The client first read the host address and port, created a socket, and then connected to the socket. It then prompts the user for text, sends it to the server and displays the reply. The server first gathers the address and port information, creates a socket, binds the socket to the server, listens, checks the connection, and replies. To accomplish this, many common socket functions were used such as the struct sockaddr_in svr_address, memset, connect, etc. 

To avoid complexity in the server code and to support simultaneous connections at the same time, I have used "select" system call for synchronous multiplexed communication. It basically selects one available activity from read, write or error file descriptors given to its argument. This allows simultaneous connection handling without the need of multi-threading or forking(that way the program would be a lot more complex than it should be). "select" doesnt create new process like fork(), it just lets the current process know if there is any available activity (read or write activity). It works like a multiplexer. 



TO RUN THE PROGRAM
==================

Run make to compile and build the programs.

To run server at port 8080(example, can be any number) type - 
./echos 8080

To run the client at host 127.0.0.1(example) and port 8080(server name) type -
./echo 127.0.0.1 8080

The user can then input data and the server will echo it back to the client 

Enter EOF or "quit" (without the quotes) to exit the client.
