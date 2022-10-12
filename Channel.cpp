//
// Created by Chaos Sherill on 10/7/22.
//

#include "Channel.hpp"

Channel::Channel(const std::string &name,const std::string pass, User* user,Postman *postman):_postman(postman),
                                                                                                _nameChannel(name),
                                                                                                _password(pass) {
    _userList.push_back(user);
    _operList.push_back(user);
    if(!this->_password.empty())
        setMode(passOnly);
}

Channel::~Channel() {}

void Channel::addUser(User *callUser,User *user) {
    if(hasMode(limited)) {
        if (_userList.size() >= _limited) {
            _postman->sendReply(callUser->getSocket(),
                                ERR_CHANNELISFULL(callUser->getNickname(),
                                                  this->_nameChannel));
            return;
        }
    }
    if (isByUser(user) ) {
        if (hasMode(inviteOnly)) {
            if (isByOper(callUser))
                _postman->sendReply(callUser->getSocket(),
                                    ERR_USERONCHANNEL(callUser->getNickname(),
                                                        user->getNickname(),
                                                        this->_nameChannel));
            else if (callUser == user)
                _postman->sendReply(callUser->getSocket(),
                                    ERR_INVITEONLYCHAN(callUser->getNickname(),
                                                        this->_nameChannel));
            else
                _postman->sendReply(callUser->getSocket(),
                                    ERR_CHANOPRIVSNEEDED(callUser->getNickname(),
                                                         this->_nameChannel));
        }
        else
            _postman->sendReply(callUser->getSocket(),
                                ERR_USERONCHANNEL(callUser->getNickname(),
                                                                         user->getNickname(),
                                                                         this->_nameChannel));
    }
    else {
        if (hasMode(inviteOnly)) {
            if (isByOper(callUser))
                _userList.push_back(user);
            else
                _postman->sendReply(callUser->getSocket(),
                                    ERR_CHANOPRIVSNEEDED(callUser->getNickname(), this->_nameChannel));
        }
        else
            _userList.push_back(user);
    }
}

void Channel::addOper(User* callUser,User *user) {
        if(!isByOper(user))
            _operList.push_back(user);
}

void Channel::sendEveryone(std::string send, User * sendUser) {
    for(std::vector<User*>::iterator    iterUser = _userList.begin();
                                        iterUser != _userList.end();
                                        ++iterUser)
        if(*iterUser != sendUser)
            _postman->sendReply((*iterUser)->getSocket(), send);
}

void Channel::setLimit(int limit) {
    if(hasMode(limited))
        this->_limited = limit;
}

void Channel::setMode(Mode mode) {

}

bool Channel::hasMode(Mode mode) {
    return ((this->_modes & mode) == mode);
}