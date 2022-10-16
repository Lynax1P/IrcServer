//
// Created by Chaos Sherill on 10/16/22.
//

#include "../UserService.hpp"

void UserService::oper(std::vector<std::string> request, int idUser) {
    std::vector<std::string>        argCount;
    if (!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if (request.size() > 2)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "OPER, you can't use ':',"));
    else if ((argCount = utils::splitBySpace(request[SECOND])).size() != 2)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "OPER,"));
    else if (!(std::equal(argCount[FIRST].begin(),argCount[FIRST].end(), "csherill")))
        _postman->sendReply(idUser, ERR_PASSWDMISMATCH(_users[idUser]->getNickname()));
    else if (!(std::equal(argCount[SECOND].begin(),argCount[SECOND].end(), "lirO")))
        _postman->sendReply(idUser, ERR_PASSWDMISMATCH(_users[idUser]->getNickname()));
    else
    {
        _postman->sendReply(idUser, RPL_YOUREOPER(_users[idUser]->getNickname()));
        _operList.push_back(_users[idUser]);
        _users[idUser]->setMode(userOper);
    }
}