//
// Created by Chaos Sherill on 10/7/22.
//

#ifndef IRC_CHANNEL_H
#define IRC_CHANNEL_H

#include "User.hpp"
enum Mode {
    none = 0,               // 0000000000
    oper = 1 << 0,          // 0000000001
    invite_only = 1 << 1,   // 0000000010
    limited = 1 << 2,       // 0000000100
    protectedTopic = 1 << 3,         // 0000001000
};

class Channel {
private:
    std::string                 _nameChanel;
    std::string                 _password;
    std::vector<User *>         _idUser;
    std::vector<User *>         _idAdmin;
    std::vector<std::string>    _historyMassage;
    int                         _modes;
    int                         _limited;
public:
    Channel(std::vector<std::string> &);
    ~Channel();


protected:
};


#endif //IRC_CHANNEL_H
