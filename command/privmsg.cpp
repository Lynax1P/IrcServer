//
// Created by Chaos Sherill on 10/5/22.
//

#include "../UserService.hpp"

void UserService::privmsg(std::vector<std::string> request, int idUser) {
    void*    reply = nullptr;
    std::vector<std::string> countTarget;
    if(!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if (request.size() != 3 || (countTarget = utils::splitBySpace(request[SECOND])).size() != 1)
    {
        if(request.size() <= 2)
            _postman->sendReply(idUser, ERR_NORECIPIENT(_users[idUser]->getNickname(), "JOIN"));
        else
            _postman->sendReply(idUser, ERR_TOOMANYTARGETS(_users[idUser]->getNickname(), request[SECOND]));
    }
    else if((reply = findUserByNickname(request[1])) == nullptr &&
                _channels.find(countTarget[FIRST]) == _channels.end())
    {
        if (reply == nullptr)
            _postman->sendReply(idUser, ERR_NOSUCHNICK(_users[idUser]->getNickname(), countTarget[FIRST]));
        else
            _postman->sendReply(idUser, ERR_NOSUCHCHANNEL(_users[idUser]->getNickname(), countTarget[FIRST]));
    }
    else if(_channels.find(countTarget[FIRST]) != _channels.end())
        _channels[countTarget[FIRST]]->sendEveryone(RPL_PRIVMSG(_users[idUser]->getNickname(),
                                                                _channels[countTarget[FIRST]]->getChannelname(),
                                                                request[THIRD]), _users[idUser]);

    else if(reply != nullptr)
    {
        if (((User *) reply)->isAway())
            _postman->sendReply(idUser, RPL_AWAY(_users[idUser]->getNickname(),
                                                 ((User *) reply)->getNickname(),
                                                 ((User *) reply)->getAwayMessege()));
        else
            _postman->sendReply(((User *) reply)->getSocket(), RPL_PRIVMSG(
                    _users[idUser]->getNickname(),
                    ((User *) reply)->getNickname(),
                    request[THIRD]));
    }
}