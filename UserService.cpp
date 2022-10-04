//
// Created by Chaos Sherill on 9/3/22.
//

#include "UserService.hpp"

UserService::UserService(const std::string &password, Postman *postman):
            _password(password),
            _postman(postman) {
//    _commands["PASS"] = &UserService::pass;
//    _commands["USER"] = &UserService::user;
//    _commands["NICK"] = &UserService::nick;
//    _commands["JOIN"] = &UserService::join;
//    _commands["KICK"] = &UserService::kick;
//    _commands["PRIVMSG"] = &UserService::privmsg;
//    _commands["NOTICE"] = &UserService::notice;
//    _commands["AWAY"] = &UserService::away;
//    _commands["PING"] = &UserService::ping;
//    _commands["PONG"] = &UserService::pong;
//    _commands["QUIT"] = &UserService::quit;
//    _commands["ISON"] = &UserService::ison;
//    _commands["NAMES"] = &UserService::names;
//    _commands["TOPIC"] = &UserService::topic;
//    _commands["MODE"] = &UserService::mode;
//    _commands["PART"] = &UserService::part;
//    _commands["WHO"] = &UserService::who;
//    _commands["BOT"] = &UserService::bot;
//    _commands["INVITE"] = &UserService::invite;
//    _commands["WALLOPS"] = &UserService::wallops;
}

void UserService::addUser(int clientSocket, const std::string &host) {
    _users[clientSocket] = new User(clientSocket, host);
    std::cout << "[CONNECTION # " << clientSocket << ' ' << host << "]\n";
}

void UserService::removeUser(int socketClient) {
    std::cout << "////Erasing " + _users[socketClient]->getNickname() << std::endl;
//    for(std::vector<>();;)
//    {
//
//    }
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
    std::cout << request << '\n';
}

bool UserService::isConnected(int idUser) {
    return _users.at(idUser)->isConnected();
}