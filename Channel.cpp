//
// Created by Chaos Sherill on 10/7/22.
//

#include "Channel.hpp"

Channel::Channel(const std::string &name,const std::string pass, User* user,Postman *postman):_postman(postman),
                                                                                                _nameChannel(name),
                                                                                                _password(pass), _modes(0), _limited() {
    _userList.push_back(user);
    _operList.push_back(user);
    firstMsg(user);
    if(!this->_password.empty())
        setMode(passOnly);
}

Channel::~Channel() {}


void Channel::addUser(User *callUser, User *user) {
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
            if (!isByOper(callUser))
                _postman->sendReply(callUser->getSocket(),
                                    ERR_CHANOPRIVSNEEDED(callUser->getNickname(), this->_nameChannel));
            else
            {
                _userList.push_back(user);
                firstMsg(user);
            }
        }
        else{
            _userList.push_back(user);
            firstMsg(user);
        }
    }
}

void Channel::addOper(User* callUser,User *user) {
        if(!isByOper(user))
            _operList.push_back(user);
}

void Channel::firstMsg(User *newUser) {

    std::string     wlcMsg = "Welcome " + newUser->getNickname() +
                                " to join us in the channel " + this->_nameChannel +
                                ". Have a nice chat!";
    std::string     bufHistoryMsg = "";
    sendEveryone(RPL_JOIN(newUser->getNickname(), this->_nameChannel), nullptr);
    for(std::vector<std::string>::iterator iterHistoryMsg = _historyMassage.begin();
                                            iterHistoryMsg != _historyMassage.end(); ++iterHistoryMsg)
        bufHistoryMsg += *iterHistoryMsg;
    _postman->sendReply(newUser->getSocket(),bufHistoryMsg);
    sendEveryone(RPL_PRIVMSG(this->_nameChannel, this->_nameChannel, wlcMsg), nullptr);
}

void Channel::sendEveryone(std::string const &send, User * sendUser) {
    if(!isByUser(sendUser) && sendUser != nullptr)
        _postman->sendReply(sendUser->getSocket(), ERR_NOTONCHANNEL(sendUser->getNickname(),this->_nameChannel));
    for(std::vector<User*>::iterator    iterUser = _userList.begin();
                                        iterUser != _userList.end(); ++iterUser)
    {
        if(*iterUser != sendUser)
            _postman->sendReply((*iterUser)->getSocket(), send);
    }
    _historyMassage.push_back(send);
    if(_historyMassage.size() > 100)
        _historyMassage[0].erase();
}

bool Channel::isByUser(User *user) {
    if(std::find(_userList.begin(), _userList.end(), user) != _userList.end())
        return true;
    return false;
}

bool Channel::isByOper(User *user) {
    if(std::find(_operList.begin(), _operList.end(), user) != _operList.end())
        return true;
    return false;
}

const std::string &Channel::getChannelname() const {return this->_nameChannel;}

void Channel::setLimit(int limit) {
    if(hasMode(limited))
        this->_limited = limit;
}

void Channel::setMode(Mode mode) {

}

bool Channel::hasMode(Mode mode) {
    return ((this->_modes & mode) == mode);
}

