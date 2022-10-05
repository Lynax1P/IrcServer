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

#define RPL_PRIVMSG(sender, recipient, msg)             (":" + (sender) + " PRIVMSG " + (recipient) + " :"+ (msg))


//_________ERRORS__________________________
#define ERR_UNKNOWNCOMMAND(nickname, command)           (":ircserv 421 " + (nickname) + ' ' + (command) + " :Unknown command")
#define ERR_TOOMANYTARGETS(nickname, target)            (":ircserv 407 " + (nickname) + ' ' + (target) + " :Duplicate recipients. No message delivered")
//_________PASS____________________________
#define ERR_NOTREGISTERED(nickname)                     (":ircserv 451 " + (nickname) + " :You have not registered")
#define ERR_NEEDMOREPARAMS(nickname, command)           (":ircserv 461 " + (nickname) + ' ' + (command) + " :Not enough parameters")
#define ERR_ALREADYREGISTRED(nickname)                  (":ircserv 462 " + (nickname) + " :You may not reregister")
#define ERR_PASSWDMISMATCH(nickname)                    (":ircserv 464 " + (nickname) + " :Password incorrect")


#define ERR_NORECIPIENT(nickname, command)      (":ircserv 411 " + (nickname) + " :No recipient given " + (command))
#define ERR_NOTEXTTOSEND(nickname)              (":ircserv 421 " + (nickname) + " :No text to send")

#define ERR_UMODEUNKNOWNFLAG(nickname)                  (":ircserv 501 " + (nickname) + " :Unknown MODE flag")
#define ERR_USERSDONTMATCH(nickname)                    (":ircserv 502 " + (nickname) + " :Cant change mode for other users")
#define ERR_CHANNELISFULL(nickname, channel)            (":ircserv 471 " + (nickname) + ' ' + (channel) + " :Cannot join channel (+l)")
#define ERR_INVITEONLYCHAN(nickname, channel)           (":ircserv 473 " + (nickname) + ' ' + (channel) + " :Cannot join channel (+i)")
#define ERR_NOPRIVILEGES(nickname)                      (":ircserv 481 " + (nickname) + " :Permission Denied- You're not an IRC operator")

#endif //IRC_POSTMAN_HPP
