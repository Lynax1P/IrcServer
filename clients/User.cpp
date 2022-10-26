//
// Created by Chaos Sherill on 9/5/22.
//

#include "User.hpp"
userc::userc(int socket, const std::string &host): _socket(socket),
                                                   _registred(false),
                                                   _connected(true),
                                                   _host(host){
    _nickname = "user";
}

userc::~userc() {}

const std::string   &userc::getNickname() const {return this->_nickname;}
const std::string   &userc::getUsername() const {return this->_username;}
const std::string   &userc::getRealname() const {return this->_realname;}
const int           &userc::getSocket() const {return this->_socket;}
const std::string   &userc::getAwayMessege() const {return this->_awayMessage;}

bool                userc::isAway() const {return !(this->_awayMessage.empty());}
bool                userc::isConnected() const {return this->_connected;}
const bool          &userc::isRegistred() const {return this->_registred;}
bool                userc::isAuthenticated() const {return this->_registred && this->_nickname != "user" && !(this->_realname.empty());}

void userc::setNickname(const std::string &nickname) { this->_nickname = nickname;}
void userc::setUsername(const std::string &username) { this->_username = username;}
void userc::setRealname(const std::string &realname) { this->_realname = realname;}
void userc::setServerName(const std::string &serverName) { this->_serverName = serverName;}
void userc::setRegistred(bool value) { this->_registred = value;}
void userc::setConnected(bool connect) { this->_connected = connect;}
void userc::setAwayMessage(const std::string &awayMsg) { this->_awayMessage = awayMsg;}

std::string userc::getFullname() const { return this->_nickname + '!' + this->_nickname + '@' + _host;}
void        userc::setMode(UserMode flag) { this->_modes |= flag;}
void        userc::unsetMode(UserMode flag) { this->_modes &= (~flag);}
bool        userc::hasMode(UserMode flag) const { return ((_modes & flag) == flag);}

std::string userc::showMode() const {
    std::string show;

    if (hasMode(userOper))
        show += 'o';
    if (hasMode(wallopsOff))
        show += 'w';
    if (hasMode(silence))
        show += 's';
    if (hasMode(invisibility))
        show += 'i';
    return show.empty() ? "" : '+' + show;
}
