//
// Created by Chaos Sherill on 10/7/22.
//

#include "Channel.hpp"

Channel::Channel(const std::string &name,const std::string pass, User* user,Postman *postman):_postman(postman),
                                                                                                _nameChannel(name),_password(pass), _modes(0), _limited() {
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
                _postman->sendReply(callUser->getSocket(),ERR_INVITEONLYCHAN(callUser->getNickname(), this->_nameChannel));
            else
                _postman->sendReply(callUser->getSocket(),ERR_CHANOPRIVSNEEDED(callUser->getNickname(), this->_nameChannel));
        }
        else
            _postman->sendReply(callUser->getSocket(),ERR_USERONCHANNEL(callUser->getNickname(),user->getNickname(),
                                                                                this->_nameChannel));
    }
    else {
        if (hasMode(inviteOnly)) {
            if (!isByOper(callUser))
                _postman->sendReply(callUser->getSocket(),ERR_CHANOPRIVSNEEDED(callUser->getNickname(), this->_nameChannel));
            else {
                _userList.push_back(user);
                firstMsg(user);
            }
        }
        else if (isByUser(callUser) || callUser == user) {
            _userList.push_back(user);
            firstMsg(user);
        }
        else
            _postman->sendReply(callUser->getSocket(), ERR_NOTONCHANNEL(callUser->getNickname(),this->_nameChannel));
    }
}

void Channel::addOper(User *user) {
    if(!isByOper(user))
        _operList.push_back(user);
}

void Channel::addOper(User* callUser,User *user) {
    if(isByOper(callUser))
        if(!isByOper(user))
            _operList.push_back(user);
}

void Channel::removeOper(User *user) {
    _operList.erase(std::find(_operList.begin(), _operList.end(), user));
}

void Channel::removeOper(User *callUser, User *user) {
    if(isByOper(callUser))
        _operList.erase(std::find(_operList.begin(), _operList.end(), user));
}

void Channel::removeUser(User *user) {
    if(!isByUser(user))
        _postman->sendReply(user->getSocket(), ERR_NOTONCHANNEL(user->getNickname(), this->_nameChannel));
    else {
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
}

void Channel::sendEveryone(std::string const &send, User * sendUser) {
    if(!isByUser(sendUser) && sendUser != nullptr)
        _postman->sendReply(sendUser->getSocket(), ERR_NOTONCHANNEL(sendUser->getNickname(),this->_nameChannel));
    for(std::vector<User*>::iterator    iterUser = _userList.begin(); iterUser != _userList.end(); ++iterUser){
        if(*iterUser != sendUser)
            _postman->sendReply((*iterUser)->getSocket(), send);
    }
    _historyMassage.push_back(send + "\r\n");
    if(_historyMassage.size() > 500)
        _historyMassage[0].erase();
}

void Channel::sendNamesOnline(User *user) {
    if(!isByUser(user))
        _postman->sendReply(user->getSocket(), ERR_NOTONCHANNEL(user->getNickname(), this->_nameChannel));
    else{
        for(std::vector<User *>::iterator itUserlist = _userList.begin(); itUserlist != _userList.end(); ++itUserlist)
            _postman->sendReply(user->getSocket(),
                                RPL_NAMREPLY(user->getNickname(), this->_nameChannel, (*itUserlist)->getFullname()));
        _postman->sendReply(user->getSocket(), RPL_ENDOFNAMES(user->getNickname(), this->_nameChannel));
    }
}

void Channel::displayTopic(User *user) {
    if(_topic.empty())
        _postman->sendReply(user->getSocket(), RPL_NOTOPIC(user->getNickname(), this->_nameChannel));
    else
        _postman->sendReply(user->getSocket(), RPL_TOPIC(user->getNickname(), this->_nameChannel, _topic));
}

void Channel::displayInfo(User *user) {
    _postman->sendReply(user->getSocket(), RPL_LIST(user->getNickname(),this->_nameChannel, std::to_string(_userList.size()), _topic));
}
const std::string   &Channel::getChannelname() const {return this->_nameChannel;}
const std::string   &Channel::getTopic() const {return this->_topic;}
int                 Channel::getLimit() const {return this->_limited;}

const std::vector<User *> &Channel::getUserlist() const {return this->_userList;}
const std::vector<User *> &Channel::getOperlist() const {return this->_operList;}



void Channel::setPass(std::string &pass) { this->_password = pass;}
void Channel::setTopic(const std::string &topic) { this->_topic = topic; }
void Channel::setTopic(const std::string &topic, User* callUser) { if(isByOper(callUser)) this->_topic = topic; }
void Channel::setLimit(int limit) { this->_limited = limit;}
void Channel::kickUser(User *callUser, User *user) {
    if(!isByOper(callUser))
        _postman->sendReply(callUser->getSocket(), ERR_CHANOPRIVSNEEDED(callUser->getNickname(),this->_nameChannel));
    else if (!isByUser(user))
        _postman->sendReply(callUser->getSocket(), ERR_NOTONCHANNEL(user->getNickname(),this->_nameChannel));
    else {
        sendEveryone(RPL_KICK(callUser->getNickname(),this->_nameChannel, user->getNickname(),"KICK"), nullptr);
        removeUser(user);
    }
}

void Channel::kickUser(User *callUser, User *user, std::string &comment) {
    if(!isByOper(callUser))
        _postman->sendReply(callUser->getSocket(), ERR_CHANOPRIVSNEEDED(callUser->getNickname(),this->_nameChannel));
    else if (!isByUser(user))
        _postman->sendReply(callUser->getSocket(), ERR_NOSUCHNICK(user->getNickname(),this->_nameChannel));
    else {
        sendEveryone(RPL_KICK(callUser->getNickname(),this->_nameChannel, user->getNickname(),comment), nullptr);
        removeUser(user);
    }
}

User *Channel::findUserByNickname(const std::string &nickname) {
    std::vector<User*>::iterator findUser;
    for(findUser = _userList.begin(); findUser != _userList.end(); ++findUser)
    {
        if(nickname == (*findUser)->getNickname())
            return *findUser;
    }
    return nullptr;
}

User *Channel::findOperByNickname(const std::string &nickname) {
    std::vector<User*>::iterator findUser;
    for(findUser = _operList.begin(); findUser != _operList.end(); ++findUser)
    {
        if(nickname == (*findUser)->getNickname())
            return *findUser;
    }
    return nullptr;
}


bool Channel::isByUser(User *user) {
    if(std::find(_userList.begin(), _userList.end(), user) != _userList.end())
        return true;
    return false;
}

bool Channel::isByOper(User *user) {
    if(user->hasMode(userOper))
        return true;
    if(std::find(_operList.begin(), _operList.end(), user) != _operList.end())
        return true;
    return false;
}

void Channel::setMode(Mode mode) { this->_modes |= mode; }
void Channel::unsetMode(Mode mode) { this->_modes &= (~mode); }
bool Channel::hasMode(Mode mode) const { return ((this->_modes & mode) == mode);}
void Channel::changeMode(std::vector<std::string> &arguments, User *callUser) {
    User *pUser;
    if (isByOper(callUser)) {
        if (!utils::isValidChannelMode(arguments[1]))
            _postman->sendReply(callUser->getSocket(), ERR_UNKNOWNCOMMAND(callUser->getNickname(), "MODE"));
        else if (arguments[1][0] == '+') {
            if (arguments[1].find('i') != std::string::npos) {
                setMode(inviteOnly);
                _postman->sendReply(callUser->getSocket(),RPL_MODE(callUser->getFullname(), this->_nameChannel, "+i : active inviteonly"));
            }
            if (arguments[1].find('t') != std::string::npos) {
                setMode(protectedTopic);
                _postman->sendReply(callUser->getSocket(), RPL_MODE(callUser->getFullname(), this->_nameChannel,"+t :only the operator can change the topiс"));
            }
            if (arguments[1].find('l') != std::string::npos) {
                if (arguments.size() != 3)
                    _postman->sendReply(callUser->getSocket(), ERR_NEEDMOREPARAMS(callUser->getNickname(), "MODE"));
                else {
                    setMode(limited);
                    setLimit(std::stoi(arguments[2]));
                    _postman->sendReply(callUser->getSocket(), RPL_MODE(callUser->getFullname(), this->_nameChannel,"+l :active limit" + arguments[2]));
                }
            }
            if (arguments[1].find('p') != std::string::npos) {
                if (arguments.size() != 3)
                    _postman->sendReply(callUser->getSocket(), ERR_NEEDMOREPARAMS(callUser->getNickname(), "MODE"));
                else {
                    setMode(passOnly);
                    setPass(arguments[2]);
                    _postman->sendReply(callUser->getSocket(), RPL_MODE(callUser->getFullname(), this->_nameChannel,"+p :active private mod"));
                }
            }
            if (arguments[1].find('o') != std::string::npos) {
                if (arguments.size() != 3)
                    _postman->sendReply(callUser->getSocket(), ERR_NEEDMOREPARAMS(callUser->getNickname(), "MODE"));
                else if ((pUser = findUserByNickname(arguments[2])) == nullptr)
                    _postman->sendReply(callUser->getSocket(), ERR_NOSUCHNICK(callUser->getNickname(), arguments[2]));
                else {
                    addOper(pUser);
                    sendEveryone(RPL_MODE(callUser->getFullname(), this->_nameChannel, "+o :" + pUser->getNickname()),nullptr);
                }
            }
        } else if (arguments[1][0] == '-') {
            if (arguments[1].find('i') != std::string::npos) {
                unsetMode(inviteOnly);
                _postman->sendReply(callUser->getSocket(),RPL_MODE(callUser->getFullname(), this->_nameChannel, "-i : deactive inviteonly"));
            }
            if (arguments[1].find('l') != std::string::npos) {
                unsetMode(limited);
                setLimit(0);
                _postman->sendReply(callUser->getSocket(), RPL_MODE(callUser->getFullname(), this->_nameChannel,
                                                                    "-l :deactive limit" + arguments[2]));
            }
            if (arguments[1].find('t') != std::string::npos) {
                _postman->sendReply(callUser->getSocket(), RPL_MODE(callUser->getFullname(), this->_nameChannel,"-t :everyone can change the topic"));
            }
            unsetMode(protectedTopic);
            if (arguments[1].find('p') != std::string::npos) {
                unsetMode(passOnly);;
                _password.clear();
                _postman->sendReply(callUser->getSocket(),RPL_MODE(callUser->getFullname(), this->_nameChannel, "-p :deactive private mod"));
            }
            if (arguments[1].find('o') != std::string::npos) {
                if (arguments.size() != 3)
                    _postman->sendReply(callUser->getSocket(), ERR_NEEDMOREPARAMS(callUser->getNickname(), "MODE"));
                else if ((pUser = findOperByNickname(arguments[2])) != nullptr)
                    _postman->sendReply(callUser->getSocket(), ERR_NOSUCHNICK(callUser->getNickname(), arguments[2]));
                else {
                    removeOper(pUser);
                    sendEveryone(RPL_MODE(callUser->getFullname(), this->_nameChannel, "-o :" + pUser->getNickname()),nullptr);
                }
            } else
                _postman->sendReply(callUser->getSocket(), ERR_UNKNOWNCOMMAND(callUser->getNickname(), "MODE"));
        }
    }
}
