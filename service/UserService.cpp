//
// Created by Chaos Sherill on 9/3/22.
//

#include "UserService.hpp"

UserService::UserService(const std::string &password, Postman *postman):
            _password(password),
            _postman(postman) {
    _commands["PASS"] = &UserService::pass;
    _commands["USER"] = &UserService::user;
    _commands["NICK"] = &UserService::nick;
    _commands["JOIN"] = &UserService::join;
    _commands["KICK"] = &UserService::kick;
    _commands["PRIVMSG"] = &UserService::privmsg;
    _commands["NOTICE"] = &UserService::notice;
    _commands["AWAY"] = &UserService::away;
    _commands["PING"] = &UserService::ping;
    _commands["QUIT"] = &UserService::quit;
    _commands["LIST"] = &UserService::list;
    _commands["ISON"] = &UserService::ison;
    _commands["NAMES"] = &UserService::names;
    _commands["TOPIC"] = &UserService::topic;
    _commands["MODE"] = &UserService::mode;
    _commands["PART"] = &UserService::part;
    _commands["OPER"] = &UserService::oper;
    _commands["WHO"] = &UserService::who;
//    _commands["BOT"] = &UserService::bot;
    _commands["INVITE"] = &UserService::invite;
    _commands["WALLOPS"] = &UserService::wallops;
}

void UserService::addUser(int clientSocket, const std::string &host) {
    _users[clientSocket] = new User(clientSocket, host);
    std::cout << "[CONNECTION # " << clientSocket << ' ' << host << "]\n";
}

void UserService::addOper(int idUser) {
    if((std::find(_operList.begin(), _operList.end(), _users[idUser])) == _operList.end())
    {
        _postman->sendReply(idUser, RPL_YOUREOPER(_users[idUser]->getNickname()));
        _operList.push_back(_users[idUser]);
        _users[idUser]->setMode(userOper);
    }
}

void UserService::removeOper(int idUser) {
    std::vector<User *>::iterator iterUser;
    if((iterUser = std::find(_operList.begin(), _operList.end(), _users[idUser])) != _operList.end()){
        _operList.erase(iterUser);
        _users[idUser]->unsetMode(userOper);
    }
}
void UserService::addChannel(int idUser, const std::string &name, const std::string &passChannel) {
    _channels[name] = new Channel(name, passChannel, _users[idUser], _postman);
    std::cout << "[CREATE NEW CHANNELL # " << name << "first user: " << _users[idUser]->getNickname() << "]\n";
}

void UserService::removeUser(int socketClient) {
    std::cout << "////Erasing " + _users[socketClient]->getNickname() << std::endl;
    for(std::map<std::string, Channel*>::iterator itChannel = _channels.begin(); itChannel != _channels.end(); ++itChannel)
        if(itChannel->second->isByUser(_users[socketClient]))
            itChannel->second->removeUser(_users[socketClient]);
    delete _users.at(socketClient);
    _users.erase(socketClient);
    std::cout << "user #"<< socketClient << " just left\n" << "////////////////\n";
}

void UserService::processRequest(std::string request, int clientSocket) {
    if (_users[clientSocket]->getNickname().empty())
        std::cout << "user " << clientSocket << ": " << request;
    else
        std::cout << _users[clientSocket]->getNickname() << ": " << request;
    std::vector<std::string> vecRec = utils::splitCommand(request);
    if(vecRec.empty())
        return;
    if (_commands.find(vecRec[0]) != _commands.end())
        (this->*_commands[vecRec[0]])(vecRec, clientSocket);
    removeEmptyChannel();
}

void UserService::welcomeUser(int idUser) {
    std::string a = "aa";
    _postman->sendReply(idUser, RPL_MOTDSTART(_users[idUser]->getNickname()));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "     \\\\XXXXXX//        Welcome to us!"));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "      XXXXXXXX"));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "     //XXXXXX\\\\                      OOOOOOOOOOOOOOOOOOOO"));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "    ////XXXX\\\\\\\\                     OOOOOOOOOOOOOOOOOOOO"));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "   //////XX\\\\\\\\\\\\     |||||||||||||||OOOOOOOOOOOOOOOVVVVVVVVVVVVV"));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "  ////////\\\\\\\\\\\\\\\\    |!!!|||||||||||OOOOOOOOOOOOOOOOVVVVVVVVVVV'"));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), " ////////  \\\\\\\\\\\\\\\\ .d88888b|||||||||OOOOOOOOOOOOOOOOOVVVVVVVVV'"));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "////////    \\\\\\\\\\\\\\d888888888b||||||||||||            'VVVVVVV'"));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "///////      \\\\\\\\\\\\88888888888||||||||||||             'VVVVV'"));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "//////        \\\\\\\\\\Y888888888Y||||||||||||              'VVV'"));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "/////          \\\\\\\\\\\\Y88888Y|||||||||||||| .             'V'"));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "////            \\\\\\\\\\\\|iii|||||||||||||||!:::.            '"));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "///              \\\\\\\\\\\\||||||||||||||||!:::::::."));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "//                \\\\\\\\\\\\\\\\           .:::::::::::."));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "/                  \\\\\\\\\\\\\\\\        .:::::::::::::::."));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "                    \\\\\\\\\\\\\\\\     .:::::::::::::::::::."));
    _postman->sendReply(idUser, RPL_MOTD(_users[idUser]->getNickname(), "                     \\\\\\\\\\\\\\\\"));
    _postman->sendReply(idUser, RPL_ENDOFMOTD(_users[idUser]->getNickname()));
    _postman->sendReply(idUser, RPL_WELCOME(_users[idUser]->getFullname()));

}

User *UserService::findUserByNickname(const std::string &nickname) {
    std::map<int, User*>::iterator findUser;
    for(findUser = _users.begin(); findUser != _users.end(); ++findUser)
    {
        if(nickname == findUser->second->getNickname())
            return findUser->second;
    }
    return nullptr;
}

bool UserService::isConnected(int idUser) {
    return _users.at(idUser)->isConnected();
}

void UserService::removeEmptyChannel() {
    for(std::map<std::string, Channel*>::iterator itChannel = _channels.begin();itChannel != _channels.end(); ++itChannel)
    {
        if ((*itChannel).second->getUserlist().empty()){
            delete (*itChannel).second;
            _channels.erase(itChannel);
        }
    }
}