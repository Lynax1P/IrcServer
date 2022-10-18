//
// Created by Chaos Sherill on 10/9/22.
//

#include "../UserService.hpp"

void UserService::away(std::vector<std::string> request, int idUser) {
    if(!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if(request.size() == 1 && !_users[idUser]->getAwayMessege().empty())
    {
        _postman->sendReply(idUser, RPL_UNAWAY(_users[idUser]->getNickname()));
        _users[idUser]->setAwayMessage("");
    } else if (request.size() > 1){
        if(request.size() == 3)
        {
            std::string bufString;
            bufString = request[1] + " :" + request[2];
            _postman->sendReply(idUser,RPL_NOWAWAY(_users[idUser]->getNickname()));
            _users[idUser]->setAwayMessage(bufString);
        }
        else{
            _postman->sendReply(idUser,RPL_NOWAWAY(_users[idUser]->getNickname()));
            _users[idUser]->setAwayMessage(request[1]);
        }
    }
}