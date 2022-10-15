//
// Created by Chaos Sherill on 10/13/22.
//

#include "../UserService.hpp"

void UserService::names(std::vector<std::string> request, int idUser)
{
    if (!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else
    {
        if(request.size() == 1)
        {
            for(std::map<std::string, Channel*>::iterator itChannel = _channels.begin();
                        itChannel != _channels.end(); ++itChannel)
                if(itChannel->second->isByUser(_users[idUser]))
                    itChannel->second->sendNamesOnline(_users[idUser]);
        }
        else if(request.size() == 2)
        {
            std::vector<std::string>  channelTarget = utils::splitByChar(request[SECOND], ',');
            for(std::vector<std::string>::iterator  listChannel = channelTarget.begin();
                                                    listChannel != channelTarget.end(); ++listChannel)
            {
                if(_channels.find(*listChannel) == _channels.end())
                    continue;
                else
                    _channels[*listChannel]->sendNamesOnline(_users[idUser]);
            }
        }
        else
        {
            _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "NAMES, you can't use ':'"));
        }

    }
}