//
// Created by Chaos Sherill on 9/3/22.
//

#ifndef IRC_USERSERVICE_HPP
#define IRC_USERSERVICE_HPP

#include "Postman.hpp"
#include <vector>
#include <map>
#include "Service.hpp"
#include <iostream>

class UserService : public Service {
private:
    typedef void (UserService::*commandPtr)(std::vector<std::string>, int);

    const std::string&          _password;
    Postman*                    _postman;
    std::map<int, void*>        _users;
    std::map<int, commandPtr>   _command;

public:
    UserService(const std::string&, Postman*);
    virtual ~UserService();

    void    addUser(int, const std::string&);
    void    removeUser(int);
    void    isConnection(int);
    void    welcomeUser(int);
//    void*   findUserByNickname(const std::string&);


//    void    addChannel();
//    void      removeEmptyChannel();
//    Channel*    findChannelByName(const std::sting&);

//    void    addOper()
    void    ;
protected:

};


#endif //IRC_USERSERVICE_HPP
