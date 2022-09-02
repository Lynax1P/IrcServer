//
// Created by Chaos Sherill on 7/7/22.
//

#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP
#include <sys/poll.h>
#include <vector>
#include <map>
#include <iostream>

class Server {
private:
    const std::string   _strPortServer;
    int                 _intSocketServer;
    std::vector<pollfd> _vecPollfdList;


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
    void    sendReceive();
    void    sendBack();
    bool    sendProcessed();
};


#endif //IRC_SERVER_HPP
