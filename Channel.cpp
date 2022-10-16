//
// Created by Chaos Sherill on 10/7/22.
//

#include "Channel.hpp"

Channel::Channel(const std::string &name,const std::string pass, User* user,Postman *postman):_postman(postman),
                                                                                                _nameChannel(name),
                                                                                                _password(pass), _modes(0), _limited() {
    _userList.push_back(user);
    _operList.push_back(user);
    setTopic("Welcome to join us in the channel " + this->_nameChannel + ". Have a nice chat!");
    firstMsg(user);
    if(!this->_password.empty())
        setMode(passOnly);
}

Channel::~Channel() {}


void Channel::addUser(User *callUser, User *user) {
    if(hasMode(limited)) {
        if (_userList.size() >= _limited) {
            _postman->sendReply(callUser->getSocket(), ERR_CHANNELISFULL(callUser->getNickname(), this->_nameChannel));
            return;
        }
    }
    if (isByUser(user) ) {
        if (hasMode(inviteOnly)) {
            if (isByOper(callUser))
                _postman->sendReply(callUser->getSocket(),ERR_USERONCHANNEL(callUser->getNickname(),user->getNickname(),
                                                        this->_nameChannel));
            else if (callUser == user)
                _postman->sendReply(callUser->getSocket(),ERR_INVITEONLYCHAN(callUser->getNickname(),
                                                        this->_nameChannel));
            else
                _postman->sendReply(callUser->getSocket(),ERR_CHANOPRIVSNEEDED(callUser->getNickname(),
                                                         this->_nameChannel));
        }
        else
            _postman->sendReply(callUser->getSocket(),ERR_USERONCHANNEL(callUser->getNickname(),user->getNickname(),
                                                                         this->_nameChannel));
    }
    else {
        if (hasMode(inviteOnly)) {
            if (!isByOper(callUser))
                _postman->sendReply(callUser->getSocket(),ERR_CHANOPRIVSNEEDED(callUser->getNickname(), this->_nameChannel));
            else
            {
                _userList.push_back(user);
                firstMsg(user);
            }
        }
        else if (isByUser(callUser) || callUser == user)
        {
            _userList.push_back(user);
            firstMsg(user);
        }
        else
            _postman->sendReply(callUser->getSocket(), ERR_NOTONCHANNEL(callUser->getNickname(),this->_nameChannel));
    }
}

void Channel::addOper(User* callUser,User *user) {
        if(!isByOper(user))
            _operList.push_back(user);
}

void Channel::removeUser(User *user) {
    if(!isByUser(user))
        _postman->sendReply(user->getSocket(), ERR_NOTONCHANNEL(user->getNickname(), this->_nameChannel));
    else
    {
        if (isByOper(user))
            _operList.erase(std::find(_operList.begin(), _operList.end(), user));
        _userList.erase(std::find(_userList.begin(), _userList.end(), user));
        sendEveryone(RPL_PART(user->getNickname(), this->_nameChannel, "QUITED"), nullptr);
    }
}

void Channel::firstMsg(User *newUser) {
    std::string     bufHistoryMsg = "";

    sendEveryone(RPL_JOIN(newUser->getFullname(), this->_nameChannel), nullptr);
    displayTopic(newUser);
    for(std::vector<User *>::iterator itUserList = _userList.begin(); itUserList != _userList.end(); ++itUserList){
        sendNamesOnline(*itUserList);
    }
//    sendReply(user.getServername(), user, RPL_ENDOFNAMES, name);
//    sendEveryone(RPL_PRIVMSG(this->this->_nameChannel, this->this->_nameChannel, wlcMsg), nullptr);
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
    _historyMassage.push_back(send + "\r\n");
    if(_historyMassage.size() > 500)
        _historyMassage[0].erase();
}

void Channel::displayTopic(User *user) {
    if(_topic.empty())
        _postman->sendReply(user->getSocket(), RPL_NOTOPIC(user->getNickname(), this->_nameChannel));
    else
        _postman->sendReply(user->getSocket(), RPL_TOPIC(user->getNickname(), this->_nameChannel, _topic));
}

void Channel::sendNamesOnline(User *user) {
    if(!isByUser(user))
        _postman->sendReply(user->getSocket(), ERR_NOTONCHANNEL(user->getNickname(), this->_nameChannel));
    else
    {
        for (std::vector<User *>::iterator itUserlist = _userList.begin(); itUserlist != _userList.end(); ++itUserlist)
            _postman->sendReply(user->getSocket(),
                                RPL_NAMREPLY(user->getNickname(), this->_nameChannel, (*itUserlist)->getFullname()));
        _postman->sendReply(user->getSocket(), RPL_ENDOFNAMES(user->getNickname(), this->_nameChannel));
    }
}

const std::string &Channel::getChannelname() const {return this->_nameChannel;}
const std::string &Channel::getTopic() const {return this->_topic;}
int Channel::getLimit() const {return this->_limited;}

const std::vector<User *> &Channel::getUserlist() const {return this->_userList;}
const std::vector<User *> &Channel::getOperlist() const {return this->_operList;}

void Channel::setLimit(int limit) {
    if(hasMode(limited))
        this->_limited = limit;
}

void Channel::setTopic(const std::string &topic) {
    _topic = topic;
}


void Channel::kickUser(User *callUser, User *user) {
    if(!isByOper(callUser))
        _postman->sendReply(callUser->getSocket(), ERR_CHANOPRIVSNEEDED(callUser->getNickname(),this->_nameChannel));
    else if (!isByUser(user))
        _postman->sendReply(callUser->getSocket(), ERR_NOTONCHANNEL(user->getNickname(),this->_nameChannel));
    else
    {
        sendEveryone(RPL_KICK(callUser->getNickname(),this->_nameChannel, user->getNickname(),"KICK"), nullptr);
        removeUser(user);
    }
}

void Channel::kickUser(User *callUser, User *user, std::string &comment) {
    if(!isByOper(callUser))
        _postman->sendReply(callUser->getSocket(), ERR_CHANOPRIVSNEEDED(callUser->getNickname(),this->_nameChannel));
    else if (!isByUser(user))
        _postman->sendReply(callUser->getSocket(), ERR_NOSUCHNICK(user->getNickname(),this->_nameChannel));
    else
    {
        sendEveryone(RPL_KICK(callUser->getNickname(),this->_nameChannel, user->getNickname(),comment), nullptr);
        removeUser(user);
    }
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

void Channel::setMode(Mode mode) {
    _modes |= mode;
}

bool Channel::hasMode(Mode mode) {
    return ((this->_modes & mode) == mode);
}

