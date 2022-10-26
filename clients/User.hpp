//
// Created by Chaos Sherill on 9/5/22.
//

#ifndef IRC_USER_HPP
#define IRC_USER_HPP


#include "vector"
#include "iostream"
#include "../service/utility/utils.hpp"
enum UserMode {
    UserNone = 0,					// 0000000000
    invisibility = 1 << 0,          // 0000000001
    silence = 1 << 1,          		// 0000000010
    userOper = 1 << 2,				// 0000000100
    wallopsOff = 1 << 3,       		// 0000001000
};

class userc {
private:
    const int                   _socket;
    std::string                 _nickname;
    std::string                 _username;
    std::string                 _serverName;
    std::string                 _realname;
    bool                        _registred;
    bool                        _connected;
    std::string                 _host;
    std::string                 _awayMessage;
    int                         _modes;
public:
    userc(int, const std::string&);
    ~userc();

    std::string const&  getNickname() const;
    std::string const&  getUsername() const;
    std::string const&  getRealname() const;
    std::string const&  getAwayMessege() const;
    std::string         getFullname() const;
    const int&          getSocket() const;

    bool                isAway() const;
    bool                isConnected() const;
    bool        const&  isRegistred() const;
    bool                isAuthenticated() const;

    void                setRegistred(bool);
    void                setConnected(bool);
    void                setNickname(const std::string&);
    void                setUsername(const std::string&);
    void                setRealname(const std::string&);
    void                setAwayMessage(const std::string&);
    void                setServerName(const std::string&);

    void                changeMode(std::vector<std::string> &parameters, userc* callUser);
    void                setMode(UserMode);
    void                unsetMode(UserMode);
    bool                hasMode(UserMode) const;
    std::string         showMode()const;
};


#endif //IRC_USER_HPP
