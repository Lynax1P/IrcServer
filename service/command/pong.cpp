//
// Created by Chaos Sherill on 10/6/22.
//

#include "../UserService.hpp"

void UserService::ping(std::vector<std::string> request, int idUser) {
    if(_users[idUser]->isAuthenticated())
    {
        if (request.size() < 2)
            _postman->sendReply(idUser, ERR_NOORIGIN(_users[idUser]->getNickname()));
        else
            _postman->sendReply(idUser, "PONG " + request[SECOND] + " " + _users[idUser]->getNickname());
    }
    else
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
}