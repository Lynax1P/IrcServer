//
// Created by Chaos Sherill on 9/3/22.
//

#ifndef IRC_USERSERVICE_HPP
#define IRC_USERSERVICE_HPP
#include "utility/utils.hpp"
#include "Postman.hpp"
#include <vector>
#include <map>
#include "Service.hpp"
#include <iostream>
#include "User.hpp"
#include "Channel.hpp"

#define FIRST 0
#define SECOND 1
#define THIRD   2

class UserService : public Service {
private:
    typedef	void (UserService::*commandPtr)(std::vector<std::string>, int);

    const std::string&                  _password;
    Postman*                            _postman;
    std::map<int, User*>                _users;
    std::map<std::string, Channel*>      _channels;
    std::map<std::string, commandPtr>   _commands;

public:
    UserService(const std::string&, Postman*);
    virtual ~UserService() {};

    void    addUser(int, const std::string&);
    void    addChannel(int idUser, const std::string& name,const std::string& pass);
    void    removeUser(int);
    bool    isConnected(int);
    void    welcomeUser(int);
    void    processRequest(std::string, int clientSocket);
    User*   findUserByNickname(const std::string&);


//    void    addChannel();
//    void      removeEmptyChannel();
//    Channel*    findChannelByName(const std::sting&);

//    void    addOper()

protected:
    void	pass(std::vector<std::string>, int);
    void	user(std::vector<std::string>, int);
    void	nick(std::vector<std::string>, int);
    void	join(std::vector<std::string>, int);
    void	kick(std::vector<std::string>, int);
    void	privmsg(std::vector<std::string>, int);
    void	notice(std::vector<std::string>, int);
    void	away(std::vector<std::string>, int);
    void	ping(std::vector<std::string>, int);
    void	pong(std::vector<std::string>, int){};
    void	quit(std::vector<std::string>, int);
    void	ison(std::vector<std::string>, int);
    void	names(std::vector<std::string>, int);
    void	topic(std::vector<std::string>, int);
    void	mode(std::vector<std::string>, int);
    void    part(std::vector<std::string>, int);
    void    who(std::vector<std::string>, int){};
    void    bot(std::vector<std::string>, int){};
    void    invite(std::vector<std::string>, int);
    void    wallops(std::vector<std::string>, int);
};


#endif //IRC_USERSERVICE_HPP
