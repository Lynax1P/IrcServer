//
// Created by Chaos Sherill on 9/3/22.
//

#ifndef IRC_SERVICE_HPP
#define IRC_SERVICE_HPP
#include <iostream>

class Service {
public:
    virtual void addUserService(int, const std::string&) = 0;
    virtual void removeUserService(int) = 0;
    virtual void isConnected(int) = 0;
    virtual void processRequest(std::string, int clientSocket) = 0;

    virtual ~Service() {};
};
#endif //IRC_SERVICE_HPP
