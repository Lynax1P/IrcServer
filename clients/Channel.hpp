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
    std::vector<userc *>         _userList;
    std::vector<userc *>         _operList;
    int                         _modes;
    int                         _limited;


    void                        addOper(userc *user);
    void                        removeOper(userc *user);

    void                        firstMsg(userc *newUser);
    void                        displayTopic(userc *user);

    void                        setPass(std::string &pass);
    void                        setTopic(const std::string&);

    void                        setMode(Mode);
    void                        unsetMode(Mode);
public:
    Channel(std::string const &name, std::string const pass, userc * user, Postman *);
    ~Channel();

    void                        addUser(userc *callUser, userc *user);
    void                        addOper(userc *callUser, userc *user);
    void                        removeOper(userc *callUser, userc *user);
    void                        removeUser(userc *user);
    void                        sendEveryone(std::string const &send, userc *sendUser);
    void                        sendNamesOnline(userc *user);
    void                        displayInfo(userc *user);

    std::string const           &getChannelname()const;
    std::string const           &getTopic()const;
    const int                   &getLimit()const;
    const std::vector<userc *>   &getUserlist()const;
    const std::vector<userc *>   &getOperlist()const;

    void                        setTopic(const std::string &topit, userc* callUser);
    void                        setLimit(int);

    void                        kickUser(userc *callUser, userc *user);
    void                        kickUser(userc *callUser, userc *user, std::string &comment);

    userc*                       findUserByNickname(std::string const &nickname);
    userc*                       findOperByNickname(const std::string &nickname);

    bool                        isByUser(userc *user);
    bool                        isByOper(userc *user);

//    bool                            isCheckPass(std::string);
    void                        changeMode(std::vector<std::string> &arg, userc* callUser);
    bool                        hasMode(Mode) const;
};


#endif //IRC_CHANNEL_H
