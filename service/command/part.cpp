//
// Created by Chaos Sherill on 10/16/22.
//

#include "../UserService.hpp"

void UserService::part(std::vector<std::string> request, int idUser) {
    if(!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if(request.size() > 2)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "PART, you can't use ':'"));
    else if (request.size() == 1)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "PART, you can't use ':'"));
    else
    {
        std::vector<std::string>    channelTarget = utils::splitByChar(request[SECOND], ',');
        for(std::vector<std::string>::iterator  listChannel = channelTarget.begin();
                                                listChannel != channelTarget.end(); ++listChannel)
        {
            if(_channels.find(*listChannel) == _channels.end())
                _postman->sendReply(idUser, ERR_NOSUCHCHANNEL(_users[idUser]->getNickname(), *listChannel));
            else
                _channels[*listChannel]->removeUser(_users[idUser]);
        }
    }
}