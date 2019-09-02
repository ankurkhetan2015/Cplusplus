#include <iostream>
#include <string>
#include <cstdlib>
#include <cerrno>
#include <cstring>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

using namespace std;

#define BUFFER_LEN 1025
#define MAX_BACKLOG 10 // maximum 10 pending connections
#define MAX_CLIENTS 50 // number of maximum clients to handle simultaneously

int readline(int fd, char *buffer, int buffer_len)
{
	// clear out the any previous data first
	for (int i = 0; i < buffer_len; i++)
	{
		buffer[i] = 0;
	}

	// read and return number of bytes read
	int rv = read(fd, buffer, buffer_len - 1); // keep one byte at end for null termination
	if (rv > 0)
	{
		for (int i = 0; i < rv; i++)
		{
			if (buffer[i] == '\n')
			{
				buffer[i + 1] = 0;
				break;
			}
		}

		// set a null termination char at the end anyway
		buffer[rv] = 0;
	}

	return rv;
}

int written(int fd, char *buffer)
{
	// try write to peer connection
	return send(fd, buffer, strlen(buffer), 0);
}

int main(int argc, char **argv)
{
	// check for the port argument
	if (argc < 2)
	{
		cout << argv[0] << " <port:listening port>" << endl;
		exit(EXIT_FAILURE);
	}

	uint16_t port = htons((uint16_t)atoi(argv[1]));
	struct sockaddr_in address;
	int address_len = sizeof(struct sockaddr_in);
	int server_fd, new_client_fd;
	int max_sock_fd; // tracker to be used for select call
	int sock_opt = 1;
	int sock_activity; // used in select multiplexing
	char *buffer = new char[BUFFER_LEN];
	int *client_fds = new int[MAX_CLIENTS];

	// mark all client fds available by setting them to 0
	for (int ix = 0; ix < MAX_CLIENTS; ix++)
	{
		client_fds[ix] = 0;
	}

	// create socket
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	// setup socket address for reusing
	// so that server can be restarted on same port next time
	if (setsockopt(server_fd,
		SOL_SOCKET,
		SO_REUSEADDR | SO_REUSEPORT,
		&sock_opt,
		sizeof(sock_opt)) < 0)
	{
		perror("socket option setup failed");
		exit(EXIT_FAILURE);
	}

	// setup address
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = port;

	// bind
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	// start listening
	if (listen(server_fd, MAX_BACKLOG) < 0)
	{
		perror("listen failed");
		exit(EXIT_FAILURE);
	}

	// server is listening from now on
	cout << "ECHO Server is listening on port " << argv[1] << endl;

	// socket list for select to work with
	fd_set read_fds;

	while (true)
	{
		// always reset the fd_set
		FD_ZERO(&read_fds);

		// add servers own socket to the set
		// so it could be used for incoming data
		FD_SET(server_fd, &read_fds);
		max_sock_fd = server_fd;

		// find the client socket fds that are connected
		// and also track the max number of socket fds available
		for (int ix = 0; ix < MAX_CLIENTS; ix++)
		{
			int fd = client_fds[ix];

			if (fd > 0)
			{
				// mark the client fd to be available for selection
				FD_SET(fd, &read_fds);
			}

			if (fd > max_sock_fd)
			{
				// keep track of maximum socket numbers
				max_sock_fd = fd;
			}
		}

		// get one activity, for NULL timeout it will block indefinitely
		sock_activity = select(max_sock_fd + 1, &read_fds, NULL, NULL, NULL);

		// check for error in multiplexing
		if ((sock_activity < 0) && (errno != EINTR))
		{
			perror("select activity error");
		}

		// check if server socket is set, if so there are
		// incoming connections to be checked
		if (FD_ISSET(server_fd, &read_fds))
		{
			// so theres an incoming connection
			// first accept the connection
			new_client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&address_len);
			if (new_client_fd < 0)
			{
				perror("accept failure");
				exit(EXIT_FAILURE); // this is serious failure to exit
			}

			// print out the new connection information
			cout << "New connection: socket fd = " << new_client_fd << ", address = " << inet_ntoa(address.sin_addr) << ", port = " << (int)ntohs(address.sin_port) << endl;

			// put the new connection in the clients list
			for (int ix = 0; ix < MAX_CLIENTS; ix++)
			{
				if (client_fds[ix] == 0)
				{
					client_fds[ix] = new_client_fd;
					cout << "New client is added to active connection list" << endl;
					break;
				}
			}
		}

		// walk through client list and check if they
		// have sent any data or disconnected.
		for (int cx = 0; cx < MAX_CLIENTS; cx++)
		{
			int client_fd = client_fds[cx];

			// if its 0 then we can skip
			if (client_fd == 0)
			{
				continue;
			}

			if (FD_ISSET(client_fd, &read_fds))
			{
				// try to read from the connection
				if (readline(client_fd, buffer, BUFFER_LEN) <= 0)
				{
					// if it reaches here client is disconnected
					// so mark it in the list as well
					getpeername(client_fd, (struct sockaddr *)&address, (socklen_t *)&address_len);
					cout << "Client disconnected: socket fd = " << client_fd << ", address = " << inet_ntoa(address.sin_addr) << ", port = " << (int)ntohs(address.sin_port) << endl;

					// mark it in the list
					close(client_fd);
					client_fds[cx] = 0;
				}
				else
				{
					// send the same line to the client back
					if (written(client_fd, buffer) < 0)
					{
						// some error happened mark the client as disconnected
						getpeername(client_fd, (struct sockaddr *)&address, (socklen_t *)&address_len);
						cout << "Client disconnected: socket fd = " << client_fd << ", address = " << inet_ntoa(address.sin_addr) << ", port = " << (int)ntohs(address.sin_port) << endl;

						// mark it in the list
						close(client_fd);
						client_fds[cx] = 0;
					}
				}
			}
		}
	}

	return 0;
}
