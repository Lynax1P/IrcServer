//
// Created by Chaos Sherill on 9/5/22.
//

#include "User.hpp"
User::User(int socket, const std::string &host):_socket(socket),
            _registred(false),
            _connected(true),
            _host(host){
    _nickname = "user";
}

User::~User() {}

const std::string   &User::getNickname() const {return this->_nickname;}
const std::string   &User::getUsername() const {return this->_username;}
const std::string   &User::getRealname() const {return this->_realname;}
const int           &User::getSocket() const {return this->_socket;}
const bool          &User::getRegistred() const {return this->_registred;}
const std::string   &User::getAwayMessege() const {return this->_awayMessage;}

bool                User::isAway() const {return !(this->_awayMessage.empty());}
bool                User::isConnected() const {return this->_connected;}
bool                User::isAuthenticated() const {return this->_registred && this->_nickname != "user" && !(this->_realname.empty());}

void User::setNickname(const std::string &nickname) {this->_nickname = nickname;}
void User::setUsername(const std::string &username) {this->_username = username;}
void User::setRealname(const std::string &realname) {this->_realname = realname;}
void User::setServerName(const std::string &serverName) {this->_serverName = serverName;}
void User::setRegistred(bool value) {this->_registred = value;}
void User::setConnected(bool connect) {this->_connected = connect;}
void User::setAwayMessage(const std::string &awayMsg) { this->_awayMessage = awayMsg;}

std::string User::getFullname() const { return this->_nickname + '!' + this->_nickname + '@' + _host;}
void        User::setMode(UserMode flag) {
    this->_modes |= flag;
}

void        User::unsetMode(UserMode flag) {
    this->_modes &= (~flag);
}

bool        User::hasMode(UserMode flag) const {
    return ((_modes & flag) == flag);
}

std::string User::showMode() const {
    std::string show;

    if (hasMode(UserOper))
        show += 'o';
    if (hasMode(wallopsOff))
        show += 'w';
    if (hasMode(silence))
        show += 's';
    if (hasMode(invisibility))
        show += 'i';
    return show.empty() ? "" : '+' + show;
}

