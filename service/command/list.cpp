//
// Created by Chaos Sherill on 10/16/22.
//

#include "../UserService.hpp"

void UserService::list(std::vector<std::string> request, int idUser)
{
    if (!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if(request.size() > 2)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "list, you can't use ':'"));
    else
    {
        if(request.size() == 1)
        {
            _postman->sendReply(idUser, RPL_LISTSTART(_users[idUser]->getNickname()));
            for(std::map<std::string, Channel*>::iterator itChannel = _channels.begin();
                itChannel != _channels.end(); ++itChannel)
                (*itChannel).second->displayInfo(_users[idUser]);
            _postman->sendReply(idUser, RPL_LISTEND(_users[idUser]->getNickname()));
        }
        else if(request.size() == 2)
        {
            std::vector<std::string>  channelTarget = utils::splitByChar(request[SECOND], ',');
            _postman->sendReply(idUser, RPL_LISTSTART(_users[idUser]->getNickname()));
            for(std::vector<std::string>::iterator  listChannel = channelTarget.begin();
                listChannel != channelTarget.end(); ++listChannel)
            {
                if(_channels.find(*listChannel) == _channels.end())
                    _postman->sendReply(idUser, ERR_NOSUCHCHANNEL(_users[idUser]->getNickname(), *listChannel));
                else
                    _channels[*listChannel]->displayInfo(_users[idUser]);
            }
            _postman->sendReply(idUser, RPL_LISTSTART(_users[idUser]->getNickname()));
        }
    }
}
