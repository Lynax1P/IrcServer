//
// Created by Chaos Sherill on 9/3/22.
//

#ifndef IRC_POSTMAN_HPP
#define IRC_POSTMAN_HPP
#include "iostream"
#include "map"

class Postman {
private:
    std::map<int, std::string>     _requests;
    std::map<int, std::string>     _replies;

public:
    void    sendRequest(int, const std::string&);
    void    sendReply(int, const std::string&);

    bool    hasRequest(int) const;
    bool    hasReply(int) const;

    void    clearRequest(int);
    void    clearReply(int);
    void    clear(int);

    std::string     getRequest(int);
    std::string     getReply(int);
};

//_________ERRORS__________________________
#define ERR_UNKNOWNCOMMAND(nickname, command)           (":ircserv 421 " + (nickname) + ' ' + (command) + " :Unknown command")

//_________PASS____________________________
#define ERR_NOTREGISTERED(nickname)                     (":ircserv 451 " + (nickname) + " :You have not registered")
#define ERR_NEEDMOREPARAMS(nickname, command)           (":ircserv 461 " + (nickname) + ' ' + (command) + " :Not enough parameters")
#define ERR_ALREADYREGISTRED(nickname)                  (":ircserv 462 " + (nickname) + " :You may not reregister")
#define ERR_PASSWDMISMATCH(nickname)                    (":ircserv 464 " + (nickname) + " :Password incorrect")

#endif //IRC_POSTMAN_HPP
