//
// Created by Chaos Sherill on 10/5/22.
//

#include "../UserService.hpp"

void UserService::user(std::vector<std::string> request, int idUser) {
    std::vector<std::string>    listArg;

    if(!_users[idUser]->isRegistred()) {
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    } else if (request.size() == 3 && ((listArg = utils::splitBySpace(request[SECOND])).size() == 3)) {
        for(std::map<int, User*>::iterator findOverlap = _users.begin();
                            findOverlap != _users.end();
                            ++findOverlap)
        {
            if(listArg[0] == findOverlap->second->getUsername())
            {
                _postman->sendReply(idUser, ERR_ALREADYREGISTRED(_users[idUser]->getNickname()));
                return;
            }
        }
        _users[idUser]->setUsername(listArg[FIRST]);
        _users[idUser]->setServerName(listArg[THIRD]);
        _users[idUser]->setRealname(request[THIRD]);
        if(_users[idUser]->isAuthenticated())
            welcomeUser(idUser);
    }
    else {
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(),"USER"));
    }
}