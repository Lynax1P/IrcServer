//
// Created by Chaos Sherill on 10/5/22.
//

#include "../UserService.hpp"

void UserService::user(std::vector<std::string> request, int idUser) {
    if(!_users[idUser]->getRegistred()) {
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    } else if () {

    }
}