//
// Created by Chaos Sherill on 10/12/22.
//

#include "../UserService.hpp"

static bool isValidChannelName(std::string name)
{
    int     i = 0;
    if (name[0] != '#')
        return false;
    while (name[++i] < name.size())
        if(!isalnum(name[i]))
            return false;
    return true;
}

void UserService::join(std::vector<std::string> request, int idUser) {
    if(!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if (request.size() != 2)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), request[FIRST]));
    else
    {
        std::vector<std::string> listChannel = utils::splitByChar(request[SECOND], ',');
        for(std::vector<std::string>::iterator  iterList = listChannel.begin(); iterList != listChannel.end(); ++iterList)
        {
            std::vector<std::string> countTargetNP = utils::splitBySpace(*iterList);
            if(!isValidChannelName(countTargetNP[FIRST]))
                _postman->sendReply(idUser, ERR_NOSUCHCHANNEL(_users[idUser]->getRealname(), countTargetNP[FIRST]));
            else if (countTargetNP.size() > 2)
                _postman->sendReply(idUser, ERR_NOSUCHCHANNEL(_users[idUser]->getRealname(), countTargetNP[FIRST]));
            else
            {
                if(_channels.find(countTargetNP[FIRST]) == _channels.end())
                {
                    if(countTargetNP.size() == 1)
                        addChannel(idUser, countTargetNP[FIRST], "");
                    else
                        addChannel(idUser, countTargetNP[FIRST],  countTargetNP[SECOND]);
                }
                else
                    _channels[countTargetNP[FIRST]]->addUser(_users[idUser],_users[idUser]);
            }
            continue;
        }
    }
}