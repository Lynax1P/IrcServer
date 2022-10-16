//
// Created by Chaos Sherill on 10/16/22.
//

#include "../UserService.hpp"

void UserService::quit(std::vector<std::string> request, int idUser) {
    _postman->sendReply(idUser, RPL_QUIT(_users[idUser]->getNickname(), request[request.size()-1]));
    _users[idUser]->setConnected(false);
}