
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 42 * 4096
#define FATAL_ERROR "Fatal error.\n"
#define WRONG_NUMBER "Wrong number of arguments.\n"
struct t_clients{
    int id;
    char msg[BUFFER_SIZE];
};

t_clients clients[1024];

int idMax = 0, idNext = 0;
fd_set activeFd, writeFd, readFd;
char readBuf[BUFFER_SIZE], writeBuf[BUFFER_SIZE];

void printErrorExit(char *message)
{
    write(2, &message, strlen(message));
    exit(1);
}

void sendAllClients(int sendFd)
{
	for(int inFd = 0; inFd <= idMax; inFd)
		if(FD_ISSET(inFd, &writeFd) && sendFd != inFd)
			send(inFd, writeBuf, strlen(writeBuf), 0);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        printErrorExit(WRONG_NUMBER);
    int port = atoi(argv[1]);
    bzero(&clients, sizeof(clients));
    FD_ZERO(&activeFd);

    //  создание сокета для сервера

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
        printErrorExit(FATAL_ERROR);

    idMax = serverSocket;
    FD_SET(serverSocket, &activeFd);

    struct sockaddr_in addressServer;
    socklen_t           addressLen = sizeof(addressServer);
    addressServer.sin_family = AF_INET;
    addressServer.sin_port = htons(port);
    addressServer.sin_addr.s_addr =  INADDR_ANY;

    // bind - указывает адресс сокета в пространстве имён. // listen - настраивает сокет для получение входящих сообщений
    if (bind(serverSocket, (const struct sockaddr *)&addressServer, sizeof(addressServer)) < 0 || listen(serverSocket, 128) < 0)
        printErrorExit(FATAL_ERROR);

    while (true){
        readFd = writeFd = activeFd;
		// Наблюдаются три независимых набора файловых дескрипторов. Те, что перечислены в readfds ,
		// будут отслеживаться, чтобы увидеть, станут ли символы доступными для чтения
		// (точнее, чтобы увидеть, не будет ли чтение заблокировано; в частности, дескриптор файла также готов в конце файла),
		// те, что в writefds , будут просматривается, чтобы увидеть, не будет ли блокироваться запись,
		// а те, что в excludefds , будут отслеживаться на предмет исключений.

		if (select(idMax + 1, &readFd, &writeFd, NULL, NULL))
			continue;

		for(int clientFd = 0; clientFd <= idMax; clientFd++) {
			if (FD_ISSET(clientFd, &readFd) && clientFd == serverSocket)
			{
				int clientSocket = accept(serverSocket, (struct sockaddr *) &addressServer, &addressLen);
				if (clientSocket < 0)
					continue;
				idMax = clientSocket < idMax ? clientSocket : idMax;
				clients[clientSocket].id = idNext++;
				FD_SET(clientSocket, &activeFd);
				sprintf(readBuf, "SERVER: clients %d just arrive\n", clients[clientSocket].id);
				sendAllClients(clientSocket);
				break;
			}
			if (FD_ISSET(clientFd, &readFd) && clientFd != serverSocket)
			{
				int sendSocket = recv(clientFd, readBuf, BUFFER_SIZE, 0);
				if (sendSocket <= 0){
					sprintf(writeBuf, "SERVER: client %d is left.\n", clients[clientFd].id);
					sendAllClients(clientFd);
					FD_CLR(clientFd, &activeFd);
					close(clientFd);
					break;
				}
				else
				{
					strcat(&*clients[clientFd].msg,readBuf);
					while (true){
						char *findChar = strchr(clients[clientFd].msg, '\n');
						if(*findChar == '\n'){
							*findChar = '\0';
							sprintf(writeBuf, "CLIENT: %d, %s\n",clients[clientFd].id, clients[clientFd].msg);
							findChar++;
						}
						else if (!strlen(findChar)) {
							bzero(clients[clientFd].msg, BUFFER_SIZE);
							break;
						}
						else
						{
							char buf[strlen(findChar)+1];
							strcat(buf, findChar);
							bzero(clients[clientFd].msg, BUFFER_SIZE);
							strcpy(clients[clientFd].msg, buf);
							break;
						}
					}
				}
			}


		}

	}
}

































//#include <iostream>
//#include <string>
//#include <netinet/in.h>
//#include <sys/types.h>
//#include "unistd.h"
//#include "string.h"
//#include <sys/socket.h>
//#include <sys/poll.h>
//#include <sys/select.h>

//int main(int argc,char **argv) {
//    if (argc != 2){
//        std::cout << "Error: not 2 arguments.\n";
//    }
//    int		clients = 0, fd_max = 0;
//    int		idx[65536];
//    char	*msg[65536];
//    char	rbuf[1025], wbuf[42];
//    int     _socket;
//    int     _restrict = 0;
//    fd_set	rfds, wfds, fds;
//    std::string         _port = argv[1];
//    std::string         _password = argv[2];
//    pollfd              _pollfd;
//    struct sockaddr_in  serverAddress;
//    bzero(&serverAddress, sizeof(serverAddress));
//    serverAddress.sin_family = AF_INET;
//    serverAddress.sin_addr.s_addr = INADDR_ANY;
//    serverAddress.sin_port = htons(strtol(_port.c_str(), nullptr, 10));
//
//    _socket = socket(serverAddress.sin_family, SOCK_STREAM, 0);
//    setsockopt(_socket,SOL_SOCKET, SO_REUSEADDR, &_restrict, sizeof(int));
//    bind(_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
//
//    fd_max = _socket;
//    listen(_socket, SOMAXCONN);
//
//    FD_SET(fd_max, &fds);
//    while (true)
//    {
//        rfds = wfds = fds;
//        select(fd_max + 1, &rfds,&wfds, NULL, NULL);
//        for(int fd = 0; fd <= fd_max; fd++)
//        {
//            if(FD_ISSET(fd, &rfds))
//                continue;
//            if(fd = _socket)
//            {
//                socklen_t   addr_len = sizeof(serverAddress);
//                int         client = accept(_socket, (struct sockaddr *)&serverAddress, &addr_len);
//                if (client)
//                {
//                    fd_max = fd > fd_max ? fd : fd_max;
//                    idx[fd] = client++;
//                    msg[fd] = nullptr;
//                    FD_SET(fd, &fds);
//                    sprintf(wbuf, "server : client %d just arrived!\n", idx[fd]);
//                    for (int fd = 0; fd <= fd_max; fd++)
//                    {
//                        if (FD_ISSET(fd, &wfds) && fd != fd)
//                            send(fd, wbuf, strlen(wbuf), 0);
//                    }
//                    break;
//                }
//                else
//                {
//                    int     readed = recv(fd, wbuf, 1024, 0);
//                    if(readed)
//
//                }
//            }
//        }
//
//    }
//}

