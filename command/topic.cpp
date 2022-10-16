//
// Created by Chaos Sherill on 10/16/22.
//
#include "../UserService.hpp"

void UserService::topic(std::vector<std::string> request, int idUser) {
    if (!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if (request.size() == 1)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(),"TOPIC, <command> <channel> :<topic>,"));
    else if(_channels.find(request[SECOND]) == _channels.end())
        _postman->sendReply(idUser, ERR_NOSUCHCHANNEL(_users[idUser]->getNickname(), request[SECOND]));
    else if(!(_channels[request[SECOND]]->isByUser(_users[idUser])))
        _postman->sendReply(idUser, ERR_NOTONCHANNEL(_users[idUser]->getNickname(),request[SECOND]));
    else if (_channels[request[SECOND]]->hasMode(protectedTopic) && !_channels[request[SECOND]]->isByOper(_users[idUser]))
        _postman->sendReply(idUser, ERR_CHANOPRIVSNEEDED(_users[idUser]->getNickname(), request[SECOND]));
    else if ((_channels[request[SECOND]]->hasMode(protectedTopic) && _channels[request[SECOND]]->isByOper(_users[idUser])) ||
                  !_channels[request[SECOND]]->hasMode(protectedTopic))
    {
        if(request.size() == 2)
            _channels[request[SECOND]]->setTopic("");
        else
            _channels[request[SECOND]]->setTopic(request[THIRD]);
    }
}
