//
// Created by Chaos Sherill on 10/16/22.
//

#include "../UserService.hpp"

void UserService::ison(std::vector<std::string> request, int idUser) {
    if (!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if (request.size() > 2)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "ISON, you can't use ':',"));
    else if (request.size() == 1)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "ISON"));
    else
    {
        std::vector<std::string>        namesTarget = utils::splitBySpace(request[SECOND]);
        std::string                     userOnline = "";
        userc*                           pUser;
        for(std::vector<std::string>::iterator itNames = namesTarget.begin(); itNames != namesTarget.end(); ++itNames)
            if((pUser=findUserByNickname(*itNames)) != nullptr)
                if(!pUser->hasMode(invisibility))
                    userOnline += pUser->getNickname() + ' ';
        _postman->sendReply(idUser,RPL_ISON(_users[idUser]->getNickname(), userOnline));
    }
}