//
// Created by Chaos Sherill on 7/7/22.
//

#include "Server.hpp"

#define     MAX_CONECTION   128
#define     BUFFER_SIZE      128

Server::Server(const std::string &port, const std::string &password):
        _strPortServer(),
        _intSocketServer(-1){}

Server::~Server() {terminateServ();}

void    Server::startPrimary() {
    std::cout << "[Start Initialization]";
    initServer();
    std::cout << "Initialization COMPLETE]";

    this->_vecPollfdList.push_back((pollfd){this->_intSocketServer, POLLIN, 0});
    std::vector<pollfd>::iterator   vecPollfdIter;
    while(true)
    {
        if(poll(this->_vecPollfdList.data(),this->_vecPollfdList.size(), -1) == -1){
            std::cerr << "pool failure\n";
            exit(EXIT_FAILURE);
        }
        if(_vecPollfdList[0].revents & POLLIN)
            addUserServer();
        for(vecPollfdIter = this->_vecPollfdList.begin(), vecPollfdIter != this->_vecPollfdList.end(), ++vecPollfdIter)
        {
            if(vecPollfdIter->revents & POLLHUP){
                removeUserServer(vecPollfdIter);
                break;
            }
            if(vecPollfdIter->revents & POLLOUT)
                sendBack(vecPollfdIter->fd);
            if(vecPollfdIter->revents & POLLIN)
                sendReceive(vecPollfdIter->fd);
            if(!sendProcessed(vecPollfdIter->fd)){
                removeUserServer(vecPollfdIter);
                break;
            }
        }
    }

}
void Server::initServer() {
    char        bufNameHost[BUFFER_SIZE];

    createSocket();
    gethostname(&bufNameHost[0], 128);
    std::cout << "Server start as::" << bufNameHost << ":" + this->_strPortServer + "\n";
    std::cout << "Server test listen:";
    if(listen(this->_intSocketServer, MAX_CONECTION) < 0){
        std::cerr << "listen socket failure\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Complete!!\n" <<  "Server fcntl:";
    if (fcntl(this->_intSocketServer, F_SETFL, O_NONBLOCK) < 0){
        std::cerr << "fcntl socket failure\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Complete!!\n" ;
}

void Server::createSocket() {
    struct sockaddr_in  address = {};
    int                 restrict = 1;

    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(strtol(this->_strPortServer.c_str(), nullptr, 10));

    if (this->_intSocketServer = socket(address.sin_family, SOCK_STREAM, 0) == -1 || \
          setsockopt(this->_intSocketServer, SOL_SOCKET, SO_REUSEADDR, &restrict, sizeof(int)) == -1 ||\
              bind(this->_intSocketServer, (struct sockaddr*)&address, sizeof(address)) == -1){
        std::cerr << "socket creation failure\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "socket server init \n";
    std::cout << inet_ntoa(address.sin_addr) << " Complete!!\n";
}

void Server::addUserServer() {
    struct sockaddr_in  clientAddr = {};
    socklen_t           lenClient = sizeof(clientAddr);
    int                 clientSocket = accept(_intSocketServer, (struct sockaddr*)&clientAddr, &lenClient);

    if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) < 0){
        std::cerr << "fcntl NONNBLOCK failure\n";
        exit(EXIT_FAILURE);
    }
     _vecPollfdList.push_back((pollfd){clientSocket, POLLIN | POLLOUT | POLLHUP, 0});
    char host[BUFFER_SIZE];
    if (getnameinfo((struct sockaddr*)&clientAddr,lenClient,&host[0],BUFFER_SIZE, nullptr, 0, 0)){
        std::cerr << "getnameinfo failure";
        exit(EXIT_FAILURE);
    }

}