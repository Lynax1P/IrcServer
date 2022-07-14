#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <sys/select.h>

int main(int argc,char **argv) {
    if (argc != 2){
        std::cout << "Error: not 2 arguments.\n";
    }
    int		clients = 0, fd_max = 0;
    int		idx[65536];
    char	*msg[65536];
    char	rbuf[1025], wbuf[42];
    int     _socket;
    int     _restrict = 0;
    fd_set	rfds, wfds, fds;
    std::string         _port = argv[1];
    std::string         _password = argv[2];
    pollfd              _pollfd;
    struct sockaddr_in  serverAddress;
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(strtol(_port.c_str(), nullptr, 10));
    _socket = socket(serverAddress.sin_family, SOCK_STREAM, 0);
    setsockopt(_socket,SOL_SOCKET, SO_REUSEADDR, &_restrict, sizeof(int));
    bind(_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    fd_max = _socket;
    listen(_socket, SOMAXCONN);
    FD_SET(fd_max, &fds);
    while (true)
    {
        rfds = wfds = fds;
        select(fd_max + 1, &rfds,&wfds, NULL, NULL);
        for(int fd = 0; fd <= fd_max; fd++)
        {
            if(FD_ISSET(fd, &rfds))
                continue;
            if(fd = _socket)
            {
                socklen_t   addr_len = sizeof(serverAddress);
                int         client = accept(_socket, (struct sockaddr *)&serverAddress, &addr_len);
                if (client)
                {
                    fd_max = fd > fd_max ? fd : fd_max;
                    idx[fd] = client++;
                    msg[fd] = nullptr;
                    FD_SET(fd, &fds);
                    sprintf(wbuf, "server : client %d just arrived!\n", idx[fd]);
                    for (int fd = 0; fd <= fd_max; fd++)
                    {
                        if (FD_ISSET(fd, &wfds) && fd != fd)
                            send(fd, wbuf, strlen(wbuf), 0);
                    }
                    break;
                }
                else
                {
                    int     readed = recv(fd, wbuf, 1024, 0);
                    if(readed)

                }
            }
        }

    }
}

