//
// Created by Chaos Sherill on 10/16/22.
//

#include "../UserService.hpp"

void UserService::notice(std::vector<std::string> request, int idUser) {
    void*    reply = nullptr;
    std::vector<std::string> countTarget;

    if(!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if (request.size() != 3 || (countTarget = utils::splitBySpace(request[SECOND])).size() != 1)
    {
        if(request.size() <= 2)
            _postman->sendReply(idUser, ERR_NORECIPIENT(_users[idUser]->getNickname(), "NOTICE"));
        else
            _postman->sendReply(idUser, ERR_TOOMANYTARGETS(_users[idUser]->getNickname(), request[SECOND]));
    }
    else if((reply = findUserByNickname(countTarget[FIRST])) == nullptr)
            _postman->sendReply(idUser, ERR_NOSUCHNICK(_users[idUser]->getNickname(), countTarget[FIRST]));
    else if(_channels.find(countTarget[FIRST]) != _channels.end())
        _channels[countTarget[FIRST]]->sendEveryone(RPL_PRIVMSG(_users[idUser]->getNickname(),
                                                                _channels[countTarget[FIRST]]->getChannelname(),
                                                                request[THIRD]), _users[idUser]);
    else if(!((User *) reply)->hasMode(silence))
        _postman->sendReply(((User *) reply)->getSocket(), RPL_PRIVMSG(_users[idUser]->getNickname(),
                ((User *) reply)->getNickname(),request[THIRD]));
    else
        _postman->sendReply(idUser, ERR_NORECIPIENT(_users[idUser]->getNickname(), "NOTICE, maybe the active mode is \"silence\""));
}
