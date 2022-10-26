//
// Created by Chaos Sherill on 10/16/22.
//

#include "../UserService.hpp"

void UserService::invite(std::vector<std::string> request, int idUser) {
    std::vector<std::string>        reqTarget;
    userc                            *pUser;

    if (!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if (request.size() > 2)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "INVITE, you can't use ':',"));
    else if (request.size() == 1 || (reqTarget = utils::splitBySpace(request[SECOND])).size() != 2)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "INVITE, <command> <nickname> <channelname>,"));
    else if ((pUser = findUserByNickname(reqTarget[FIRST])) == nullptr ||
                    _channels.find(reqTarget[SECOND]) == _channels.end()){
        if (pUser == nullptr)
            _postman->sendReply(idUser, ERR_NOSUCHNICK(_users[idUser]->getNickname(), reqTarget[FIRST]));
        else
            _postman->sendReply(idUser, ERR_NOSUCHCHANNEL(_users[idUser]->getNickname(), reqTarget[SECOND]));
    }
    else if (_channels[reqTarget[SECOND]]->hasMode(inviteOnly) && !_channels[reqTarget[SECOND]]->isByOper(_users[idUser]))
        _postman->sendReply(idUser, ERR_INVITEONLYCHAN(_users[idUser]->getNickname(), reqTarget[SECOND]));
    else {
        if ((pUser)->isAway())
        {
            _postman->sendReply(idUser, RPL_AWAY(reqTarget[FIRST], _users[idUser]->getNickname(),
                                                    (pUser)->getAwayMessege()));
            _channels[reqTarget[SECOND]]->addUser(_users[idUser], pUser);
        }
        else
        {
            _postman->sendReply((pUser)->getSocket(), RPL_INVITING(_users[idUser]->getFullname(), pUser->getNickname(),
                                                                   _channels[reqTarget[SECOND]]->getChannelname()));
            _postman->sendReply(idUser, RPL_INVITE(_users[idUser]->getFullname(), pUser->getNickname(),
                                                   _channels[reqTarget[SECOND]]->getChannelname()));
        }
    }
}