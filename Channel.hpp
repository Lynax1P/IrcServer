//
// Created by Chaos Sherill on 10/7/22.
//

#ifndef IRC_CHANNEL_H
#define IRC_CHANNEL_H

#include "User.hpp"
#include "Postman.hpp"

enum Mode {
    none = 0,                       // 0000000000
    oper = 1 << 0,                  // 0000000001
    inviteOnly = 1 << 1,           // 0000000010
    limited = 1 << 2,               // 0000000100
    protectedTopic = 1 << 3,        // 0000001000
    passOnly = 1 << 4,              // 0000010000
};

class Channel {
private:
    Postman*                    _postman;
    std::string                 _nameChannel;
    std::string                 _password;
    std::string                 _topic;
    std::vector<User *>         _userList;
    std::vector<User *>         _operList;
    std::vector<std::string>    _historyMassage;
    int                         _modes;
    int                         _limited;


    void                        setMode(Mode);
//    void                        unsetMode(Mode);
    bool                        hasMode(Mode);
    void                        firstMsg(User *newUser);
public:
    Channel(std::string const &name, std::string const pass,User * user, Postman *);
    ~Channel();

    void    addUser(User *callUser,User *user);
    void    addOper(User *callUser,User *user);
    void    sendEveryone(std::string const &send, User *sendUser);
    void    displayTopic(User *user);
    void    setLimit(int);
    void    setTopic(const std::string&);

    std::string const               &getTopic()const;
    std::string const               &getChannelname()const;
    int                             getLimit()const;
    const std::vector<User *>       &getUserlist()const;
    const std::vector<User *>       &getOperlist()const;


//    bool                            isCheckPass(std::string);
    bool                            isByUser(User *user);
    bool                            isByOper(User *user);
//    std::string                 showMode()const;

protected:
};


#endif //IRC_CHANNEL_H
