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
    // check for arguments
    if (argc < 3)
    {
        cout << argv[0] << " <host: host address string> <port: host port>" << endl;
        exit(EXIT_FAILURE);
    }

    // read the host address and port first
    struct sockaddr_in svr_address;
    int sock_fd;
    char *buffer = new char[BUFFER_LEN];

    memset(&svr_address, 0, sizeof(struct sockaddr_in));
    svr_address.sin_family = AF_INET;
    svr_address.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &svr_address.sin_addr) <= 0)
    {
        cout << "address convertion failed" << endl;
        exit(EXIT_FAILURE);
    }

    // create socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (connect(sock_fd, (struct sockaddr *)&svr_address, sizeof(struct sockaddr_in)) < 0)
    {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    // now prompt the user to enter some text
    // send it to the server, read back the reply
    // and print the reply until user types quit or
    // EOF is found
    string line;
    cout << "Type \"quit\" to exit the program" << endl;
    cout << "> " << flush;
    while (getline(cin, line) && line != "quit")
    {
        memset(buffer, 0, BUFFER_LEN);
        memcpy(buffer, line.c_str(), min((int)line.length(), BUFFER_LEN - 1));
        buffer[BUFFER_LEN - 1] = 0; // make sure theres a null char
        cout << "Sending: " << buffer << endl;
        if (written(sock_fd, buffer) < 0)
        {
            perror("send failure");
            close(sock_fd);
            exit(EXIT_FAILURE);
        }

        // read back
        memset(buffer, 0, BUFFER_LEN);
        if (readline(sock_fd, buffer, BUFFER_LEN) <= 0)
        {
            perror("read failure");
            close(sock_fd);
            exit(EXIT_FAILURE);
        }

        cout << "Server Sent Back: " << buffer << endl;

        cout << "> " << flush;
    }

    // exit message
    cout << "Exiting ..." << endl;

    // close connection
    close(sock_fd);

    return 0;
}
