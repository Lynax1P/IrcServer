//
// Created by Chaos Sherill on 10/13/22.
//

#include "../UserService.hpp"

void UserService::names(std::vector<std::string> request, int idUser)
{
    if (!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else
    {

    }
}