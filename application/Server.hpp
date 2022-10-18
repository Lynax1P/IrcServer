//
// Created by Chaos Sherill on 7/7/22.
//

#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP
#include <sys/poll.h>
#include <vector>
#include <map>
#include <iostream>
#include "unistd.h"
#include "netinet/in.h"
#include "stdlib.h"
#include "arpa/inet.h"
#include "sys/fcntl.h"
#include "netdb.h"
#include "../service/Postman.hpp"
#include "../service/UserService.hpp"

class Server {
private:
    const std::string   _strPortServer;
    int                 _intSocketServer;
    std::vector<pollfd> _vecPollfdList;
    Postman             _postman;
    Service*            _service;

public:
    Server(std::string const&, std::string const&);
    ~Server();

    void    startPrimary();
    void    terminateServ();

protected:
    void    initServer();
    void    createSocket();
    void    addUser();
    void    removeUser(std::vector<pollfd>::iterator);
    void    sendReceive(int);
    void    sendBack(int);
    bool    sendProcessed(int);
};


#endif //IRC_SERVER_HPP
