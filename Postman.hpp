//
// Created by Chaos Sherill on 9/3/22.
//

#ifndef IRC_POSTMAN_HPP
#define IRC_POSTMAN_HPP
#include "iostream"
#include "map"

class Postman {
private:
    std::map<int, std::string&>     _requests;
    std::map<int, std::string&>     _replies;

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


#endif //IRC_POSTMAN_HPP
