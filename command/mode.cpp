//
// Created by Chaos Sherill on 10/16/22.
//

#include "../UserService.hpp"

void UserService::mode(std::vector<std::string> request, int idUser) {
    std::vector<std::string>                argTarget;
    User*                                   pUser;
    if(!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if (request.size() > 2)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "MODE, you can't use ':',"));
    else if (request.size() == 1)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "MODE"));
    else if ((argTarget = utils::splitBySpace(request[SECOND])).size() <= 3 && argTarget.size() >= 2)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "MODE"));
    else if((pUser = findUserByNickname(argTarget[FIRST])) == nullptr && _channels.find(argTarget[FIRST]) == _channels.end())
    {
        if (pUser == nullptr)
            _postman->sendReply(idUser, ERR_NOSUCHNICK(_users[idUser]->getNickname(), argTarget[FIRST]));
        else
            _postman->sendReply(idUser, ERR_NOSUCHCHANNEL(_users[idUser]->getNickname(), argTarget[FIRST]));
    }
    else if (pUser != nullptr)
    {
        if(_users[idUser]->hasMode(userOper) || _users[idUser] == pUser)
            pUser->changeMode();
        else
            _postman->sendReply(idUser, ERR_USERSDONTMATCH(_users[idUser]->getNickname()));
    }
    else
    {
        if(_channels[argTarget[FIRST]]->isByOper(_users[idUser]))
            _channels[argTarget[FIRST]]->changeMode(argTarget, _users[idUser]);
        else if (!_channels[argTarget[FIRST]]->isByUser(_users[idUser]))
            _postman->sendReply(idUser, ERR_NOTONCHANNEL(_users[idUser]->getNickname(), argTarget[FIRST]));
        else
            _postman->sendReply(idUser, ERR_CHANOPRIVSNEEDED(_users[idUser]->getNickname(), argTarget[FIRST]));
    }
}