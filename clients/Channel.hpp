//
// Created by Chaos Sherill on 10/7/22.
//

#ifndef IRC_CHANNEL_H
#define IRC_CHANNEL_H

#include "User.hpp"
#include "../service/Postman.hpp"
#include "../service/utility/utils.hpp"
enum Mode {
    none = 0,                       // 0000000000
    oper = 1 << 0,                  // 0000000001
    inviteOnly = 1 << 1,            // 0000000010
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
    int                         _modes;
    int                         _limited;


    void                        addOper(User *user);
    void                        removeOper(User *user);

    void                        firstMsg(User *newUser);
    void                        displayTopic(User *user);

    void                        setPass(std::string &pass);
    void                        setTopic(const std::string&);

    void                        setMode(Mode);
    void                        unsetMode(Mode);
public:
    Channel(std::string const &name, std::string const pass,User * user, Postman *);
    ~Channel();

    void                        addUser(User *callUser,User *user);
    void                        addOper(User *callUser,User *user);
    void                        removeOper(User *callUser, User *user);
    void                        removeUser(User *user);
    void                        sendEveryone(std::string const &send, User *sendUser);
    void                        sendNamesOnline(User *user);
    void                        displayInfo(User *user);

    std::string const           &getChannelname()const;
    std::string const           &getTopic()const;
    const int                   &getLimit()const;
    const std::vector<User *>   &getUserlist()const;
    const std::vector<User *>   &getOperlist()const;

    void                        setTopic(const std::string &topit, User* callUser);
    void                        setLimit(int);

    void                        kickUser(User *callUser, User *user);
    void                        kickUser(User *callUser, User *user, std::string &comment);

    User*                       findUserByNickname(std::string const &nickname);
    User*                       findOperByNickname(const std::string &nickname);

    bool                        isByUser(User *user);
    bool                        isByOper(User *user);

//    bool                            isCheckPass(std::string);
    void                        changeMode(std::vector<std::string> &arg, User* callUser);
    bool                        hasMode(Mode) const;
};


#endif //IRC_CHANNEL_H
