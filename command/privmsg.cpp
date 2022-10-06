//
// Created by Chaos Sherill on 10/5/22.
//

#include "../UserService.hpp"

void UserService::privmsg(std::vector<std::string> request, int idUser) {
    User*    _userReply = nullptr;

    if(!_users[idUser]->isAuthenticated()){
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    }
    else if (request.size() != 3)
    {
        if(request.size() <= 2)
            _postman->sendReply(idUser, ERR_NORECIPIENT(_users[idUser]->getNickname(), "PASS"));
        else {
            _postman->sendReply(idUser, ERR_TOOMANYTARGETS(_users[idUser]->getNickname(), request[SECOND]));
        }
    }
    else if((_userReply = findUserByNickname(request[1])) != nullptr)
    {
        _postman->sendReply(_userReply->getSocket(), RPL_PRIVMSG(
                                                   _users[idUser]->getNickname(),
                                                   _userReply->getNickname(),
                                                   request[THIRD]));
    }
}