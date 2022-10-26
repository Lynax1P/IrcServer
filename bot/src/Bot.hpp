//
// Created by Chaos Sherill on 10/26/22.
//

#ifndef IRC_BOT_HPP
#define IRC_BOT_HPP

#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <cstdlib>
#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include "../../service/utility/utils.hpp"
#include "../../service/Postman.hpp"
#include <fstream>
class Bot {
private:
    std::string _name;
    std::string _hostname;
    std::string _port;
    std::string _pass;
    std::string _request;
    std::string _reply;
    int         _socket;
    bool        _isAuth;

    void error(std::string);
    void sendMem(std::string request);
    void resetPass();
    bool hasRequest();
    std::string getRequest();
public:
    Bot(std::string, std::string, std::string);
    ~Bot();

    void run();
    void sendBack();
    void sendReceive();
    void sendProcessed();
};

#define  RPL_PASS(pass)         ("PASS " + pass + "\r\n")
#define  RPL_NICK(nick)         ("NICK " + nick + "\r\n")
#define  RPL_REG(name,fullname) ("USER " + name  + " " + name + " " + name + " :" + fullname)
#endif //IRC_BOT_HPP
