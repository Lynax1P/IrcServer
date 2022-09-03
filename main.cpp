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
#include <cstdio>
#include <arpa/inet.h>
#define FATAL_ERROR "Fatal error.\n"
#define WRONG_NUMBER "Wrong number of arguments.\n"
#define GREY_COL "\033[37m"
#define GREEN_COL "\033[32m"
#define NO_COL "\033[0m"
#define MAX_CONNECTION 128

int main(int argc, char **argv)
{
    std::map<int, std::string>  _map;

    _map[0] = "qee\n";
    _map[1] = "qee";

    if(!_map.at(0).empty() && _map.find(0) != _map.end() &&
            _map.at(0).find('\n') != std::string::npos )
        std::cout << "not empty\n";
    else
        std::cout << "empty\n";
    if(_map.find(0) != _map.end() && !_map.at(0).empty())
        std::cout << "not empty\n";
    else
        std::cout << "empty\n";
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