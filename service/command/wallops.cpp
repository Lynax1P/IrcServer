//
// Created by Chaos Sherill on 10/16/22.
//

#include "../UserService.hpp"

void UserService::wallops(std::vector<std::string> request, int idUser) {
    if (!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if (request.size() > 2)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "wallops, you can't use ':',"));
    else
    {
        for(std::vector<userc *>::iterator itOper = _operList.begin(); itOper != _operList.begin(); ++itOper)
            _postman->sendReply((*itOper)->getSocket(), RPL_PRIVMSG(_users[idUser]->getNickname(), '*', request[SECOND]));
    }
}