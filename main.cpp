#include <iostream>
#include <sys/poll.h>
#include <vector>
#include <map>
#include "netinet/in.h"
#include "sys/socket.h"
#include <netdb.h>
#include "unistd.h"
#include "fcntl.h"
#include <cstring>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <cstdio>
#include <stdio.h>
#include <arpa/inet.h>
#define FATAL_ERROR "Fatal error.\n"
#define WRONG_NUMBER "Wrong number of arguments.\n"
#define GREY_COL "\033[37m"
#define GREEN_COL "\033[32m"
#define NO_COL "\033[0m"
#define MAX_CONNECTION 128

int main(int argc, char **argv)
{
    int socketServer;
    std::vector<pollfd>     _pollSocket;
	std::map<int, std::string>	userList;
	std::map<int, std::string>	masseger;
    {
        struct sockaddr_in addressSocket = {};
        int     choto = 1;

        bzero(&addressSocket, sizeof(addressSocket));
        addressSocket.sin_family = AF_INET;
        addressSocket.sin_addr.s_addr = INADDR_ANY;
        addressSocket.sin_port = htons(strtol(argv[1],NULL, 10));

        socketServer = socket(addressSocket.sin_family, SOCK_STREAM, 0);
        setsockopt(socketServer, SOL_SOCKET,SO_REUSEADDR, &choto, sizeof(int));
        if(bind(socketServer, (struct sockaddr*)&addressSocket, sizeof(addressSocket)) == -1)
            exit(EXIT_FAILURE); else std::cout<< "Ok Bind\n";
        std::cout << "ipv4\n" << inet_ntoa(addressSocket.sin_addr) << GREEN_COL << " [COMPLETE!]\n" << NO_COL;
    }
    {
        char buffHostName[128];
        gethostname(&buffHostName[0], 128);
        std::cout << buffHostName << " \nserver start\n";
        listen(socketServer, 128);
        fcntl(socketServer, F_SETFL, O_NONBLOCK);
    }
    _pollSocket.push_back((pollfd){socketServer, POLLIN, 0});
    std::vector<pollfd>::iterator   iteratorPollfd;

    while (true)
    {
        if(poll(_pollSocket.data(), _pollSocket.size(), -1) == -1)
        {
            std::cerr << "poll failure\n";
            exit(EXIT_FAILURE);
        }
        if(_pollSocket[0].revents & POLLIN)
		{
			struct sockaddr_in addressUser = {};
			socklen_t 		len = sizeof(addressUser);
			int 			socketClient = accept(socketServer, (struct sockaddr*)&addressUser, &len);

			if (fcntl(socketClient, F_SETFL, O_NONBLOCK) < 0)
			{
				std::cerr << "fcntl nonblock failure\n";
				exit(EXIT_FAILURE);
			}
			_pollSocket.push_back((pollfd){socketClient, POLLIN | POLLOUT | POLLHUP, 0});
			char buffer[128];
			if(getnameinfo((struct sockaddr*)&addressUser, len, &buffer[0], 128, NULL, 0,0))
			{
				std::cerr << "getnameinfo failure\n";
				exit(EXIT_FAILURE);
			}
			std::string nameUser = buffer;
			std::cout << nameUser << std::endl;
			userList[socketClient] = nameUser;
		}
		for (iteratorPollfd = _pollSocket.begin() + 1; iteratorPollfd != _pollSocket.end(); ++iteratorPollfd)
		{
			if(iteratorPollfd->revents & POLLHUP)
			{
				close(iteratorPollfd->fd);
				userList.erase(iteratorPollfd->fd);

				_pollSocket.erase(iteratorPollfd);
				break;
			}

            if(iteratorPollfd->revents & POLLOUT)
            {
				std::string 	buffMsg;
				char 		buf[10];
				if(!masseger[iteratorPollfd->fd].empty()){
					sprintf(buf,"%d",iteratorPollfd->fd);
					buffMsg += "[client ";
					buffMsg +=  userList[iteratorPollfd->fd];
					buffMsg += 	buf;
					buffMsg +=  "] ";
					buffMsg +=	masseger[iteratorPollfd->fd].c_str();
					if (send(iteratorPollfd->fd, buffMsg.c_str(), \
									buffMsg.size(), 0) == -1) {
						std::cerr << "send failure\n";
						exit(EXIT_FAILURE);
					}
					masseger[iteratorPollfd->fd].clear();

				}
            }
			if(iteratorPollfd->revents & POLLIN)
			{
				std::string 	buffMsg;
				char 	msg[21];


				for(int	countRecv = 20; countRecv == 20;countRecv = recv(iteratorPollfd->fd, &msg, 20, 0))
				{
					bzero(&*msg, 20);
					if( countRecv == -1)
					{
						std::cerr << "recv() failure\n";
						exit(EXIT_FAILURE);
					}
//					if (countRecv == 0)
//						break;
					buffMsg += msg;
				}
				std::map<int, std::string>::iterator itMapMsg = masseger.begin();
				for(;itMapMsg != masseger.end(); ++itMapMsg){
					itMapMsg->second += buffMsg;
				}
			}

		}
    }
}

































//#include <string.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include "iostream"
//
//#define GREY_COL "\033[37m"
//#define GREEN_COL "\033[32m"
//#define NO_COL "\033[0m"
//#define BUFFER_SIZE 42 * 4096
//#define FATAL_ERROR "Fatal error.\n"
//#define WRONG_NUMBER "Wrong number of arguments.\n"
//struct t_clients{
//    int id;
//    char msg[BUFFER_SIZE];
//};
//
//t_clients clients[1024];
//
//int idMax = 0, idNext = 0;
//fd_set activeFd, writeFd, readFd;
//char readBuf[BUFFER_SIZE], writeBuf[BUFFER_SIZE];
//
//void printErrorExit(char *message)
//{
//    write(1, message, strlen(message));
//    exit(1);
//}
//
//void sendAllClients(int sendFd)
//{
//	for(int inFd = 0; inFd <= idMax; inFd)
//		if(FD_ISSET(inFd, &writeFd) && sendFd != inFd)
//			send(inFd, writeBuf, strlen(writeBuf), 0);
//}
//
//int main(int argc, char **argv)
//{
//    if (argc != 2)
//        printErrorExit(WRONG_NUMBER);
//
//
//    int port = atoi(argv[1]);
//    bzero(&clients, sizeof(clients));
//    FD_ZERO(&activeFd);
//
//    //  создание сокета для сервера
//
//    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
//    if (serverSocket < 0)
//        printErrorExit(FATAL_ERROR);
//
//    idMax = serverSocket;
//    FD_SET(serverSocket, &activeFd);
//
//    struct sockaddr_in addressServer;
//    socklen_t           addressLen = sizeof(addressServer);
//    addressServer.sin_family = AF_INET;
//    addressServer.sin_port = htons(port);
//    addressServer.sin_addr.s_addr =  INADDR_ANY;
//    std::string nameServer;
//    size_t      nameLen;
//    hostent     hostInfo;
//    char buff[128];
//    gethostname(&buff[0], 128);
//    printf("server started as:%s%s%s:%s%i%s\n\n", GREEN_COL, buff, NO_COL, GREEN_COL, port, NO_COL);
//
////    gethostbyname(hostInfo.h_name);
////    std::cout << hostInfo.h_name;
////     bind - указывает адресс сокета в пространстве имён.
////	 listen - настраивает сокет для получение входящих сообщений
//    if (bind(serverSocket, (const struct sockaddr *)&addressServer, sizeof(addressServer)) < 0 || listen(serverSocket, 128) < 0)
//        printErrorExit(FATAL_ERROR);
//
//    while (true){
//        readFd = writeFd = activeFd;
//		// Наблюдаются три независимых набора файловых дескрипторов. Те, что перечислены в readfds ,
//		// будут отслеживаться, чтобы увидеть, станут ли символы доступными для чтения
//		// (точнее, чтобы увидеть, не будет ли чтение заблокировано; в частности, дескриптор файла также готов в конце файла),
//		// те, что в writefds , будут просматривается, чтобы увидеть, не будет ли блокироваться запись,
//		// а те, что в excludefds , будут отслеживаться на предмет исключений.
//
//		if (select(idMax + 1, &readFd, &writeFd, NULL, NULL))
//			continue;
//
//		for(int clientFd = 0; clientFd <= idMax; clientFd++) {
//			if (FD_ISSET(clientFd, &readFd) && clientFd == serverSocket)
//			{
//				int clientSocket = accept(serverSocket, (struct sockaddr *) &addressServer, &addressLen);
//				if (clientSocket < 0)
//					continue;
//				idMax = clientSocket < idMax ? clientSocket : idMax;
//				clients[clientSocket].id = idNext++;
//				FD_SET(clientSocket, &activeFd);
//				sprintf(readBuf, "SERVER: clients %d just arrive\n", clients[clientSocket].id);
//				sendAllClients(clientSocket);
//				break;
//			}
//			if (FD_ISSET(clientFd, &readFd) && clientFd != serverSocket)
//			{
//				int sendSocket = recv(clientFd, readBuf, BUFFER_SIZE, 0);
//				if (sendSocket <= 0){
//					sprintf(writeBuf, "SERVER: client %d is left.\n", clients[clientFd].id);
//					sendAllClients(clientFd);
//					FD_CLR(clientFd, &activeFd);
//					close(clientFd);
//					break;
//				}
//				else
//				{
//					strcat(&*clients[clientFd].msg,readBuf);
//					while (true)
//					{
//						char *findChar = strchr(clients[clientFd].msg, '\n');
//						if(*findChar == '\n'){
//							*findChar = '\0';
//							sprintf(writeBuf, "CLIENT: %d, %s\n",clients[clientFd].id, clients[clientFd].msg);
//							findChar++;
//						}
//						else if (!strlen(findChar)) {
//							bzero(clients[clientFd].msg, BUFFER_SIZE);
//							break;
//						}
//						else
//						{
//							char buf[strlen(findChar)+1];
//							strcat(buf, findChar);
//							bzero(clients[clientFd].msg, BUFFER_SIZE);
//							strcpy(clients[clientFd].msg, buf);
//							break;
//						}
//					}
//				}
//			}
//		}
//	}
//    return 1;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//-