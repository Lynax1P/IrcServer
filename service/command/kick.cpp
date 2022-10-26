//
// Created by Chaos Sherill on 10/16/22.
//

#include "../UserService.hpp"

void UserService::kick(std::vector<std::string> request, int idUser) {
    std::vector<std::string>        argTarget;
    userc*                           pUser;
    if(!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if (request.size() == 1 || (argTarget = utils::splitBySpace(request[SECOND])).size() != 2)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "KICK,"));
    else if ((pUser = findUserByNickname(argTarget[SECOND])) == nullptr ||
            _channels.find(argTarget[SECOND]) == _channels.end()){
        if (pUser == nullptr)
            _postman->sendReply(idUser, ERR_NOSUCHNICK(_users[idUser]->getNickname(), argTarget[FIRST]));
        else
            _postman->sendReply(idUser, ERR_NOSUCHCHANNEL(_users[idUser]->getNickname(), argTarget[SECOND]));
    } else {
        if(request.size() == 2)
            _channels[argTarget[SECOND]]->kickUser(_users[idUser],pUser);
        else
            _channels[argTarget[SECOND]]->kickUser(_users[idUser],pUser, request[THIRD]);
    }
}