//
// Created by Chaos Sherill on 7/7/22.
//

#include "Server.hpp"

#define     MAX_CONECTION   128
#define     BUFFER_SIZE      128

Server::Server(const std::string &port, const std::string &password):
        _strPortServer(port),
        _intSocketServer(-1),
        _postman(Postman()),
        _service(new UserService(password, &_postman)){}

Server::~Server() {terminateServ();}

void Server::terminateServ() {
    std::vector<pollfd>::iterator iter;
    for(iter = _vecPollfdList.begin(); iter != _vecPollfdList.end(); ++iter)
        removeUser(iter);
    delete _service;
}
void    Server::startPrimary() {
    std::cout << "[Start Initialization]\n";
    initServer();
    std::cout << "[Initialization COMPLETE]\n";

    this->_vecPollfdList.push_back((pollfd){this->_intSocketServer, POLLIN, 0});
    std::vector<pollfd>::iterator   vecPollfdIter;
    while(true)
    {
        if(poll(this->_vecPollfdList.data(),this->_vecPollfdList.size(), -1) == -1){
            std::cerr << "pool failure\n";
            exit(EXIT_FAILURE);
        }
        if(_vecPollfdList[0].revents & POLLIN)
            addUser();
        for(vecPollfdIter = this->_vecPollfdList.begin() + 1; vecPollfdIter != this->_vecPollfdList.end(); ++vecPollfdIter)
        {
            if(vecPollfdIter->revents & POLLHUP){
                removeUser(vecPollfdIter);
                break;
            }
            if(vecPollfdIter->revents & POLLOUT)
                sendBack(vecPollfdIter->fd);
            if(vecPollfdIter->revents & POLLIN)
                sendReceive(vecPollfdIter->fd);
            if(!sendProcessed(vecPollfdIter->fd)){
                removeUser(vecPollfdIter);
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

    if ((this->_intSocketServer = socket(address.sin_family, SOCK_STREAM, 0)) == -1 || \
          setsockopt(this->_intSocketServer, SOL_SOCKET, SO_REUSEADDR, &restrict, sizeof(int)) == -1 ||\
              bind(this->_intSocketServer, (struct sockaddr*)&address, sizeof(address)) == -1){
        std::cerr << "socket creation failure\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "socket server init \n";
    std::cout << inet_ntoa(address.sin_addr) << " Complete!!\n";
}

void Server::addUser() {
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
    this->_service->addUser(clientSocket, host);
}

void Server::sendBack(int clientSocket) {
    if (this->_postman.hasReply(clientSocket))
    {
        std::string bufMsg = _postman.getReply(clientSocket);
        if (send(clientSocket, bufMsg.c_str(), bufMsg.size(), 0) == -1)
        {
            std::cerr << "send failura\n";
            exit(EXIT_FAILURE);
        }
        std::cout << bufMsg;
    }
}

void Server::sendReceive(int clientSocket) {
    char        msg[BUFFER_SIZE];
    int         t = 0;
    bzero(&msg, BUFFER_SIZE);
    t = recv(clientSocket, &msg, BUFFER_SIZE - 1, 0);
    if(t < 0)
    {
        std::cerr << "|recv() failure|\n";
        exit(EXIT_FAILURE);
    }
    this->_postman.sendRequest(clientSocket, msg);
}

void Server::removeUser(std::vector<pollfd>::iterator pollIter) {
    close(pollIter->fd);
    _service->removeUser(pollIter->fd);
    _postman.clear(pollIter->fd);
    _vecPollfdList.erase(pollIter);
}

bool Server::sendProcessed(int clientSocket)
{
    while (_postman.hasRequest(clientSocket))
    {
        _service->processRequest(_postman.getRequest(clientSocket), clientSocket);
        if(!_service->isConnected(clientSocket))
            return false;
    }
    return true;
}