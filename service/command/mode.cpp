//
// Created by Chaos Sherill on 10/16/22.
//

#include "../UserService.hpp"

std::string changeMode(std::vector<std::string> &argMode, User *callUser, User* pUser) {
    if (callUser->hasMode(userOper) || callUser == pUser) {
        if (!utils::isValidUserMode(argMode[1])) {
            return ("MODE");
        }
        if(argMode[1][0] == '+'){
            if(argMode[1].find('o') != std::string::npos && callUser->hasMode(userOper))
                pUser->setMode(userOper);
            if(argMode[1].find('i') != std::string::npos)
                pUser->setMode(invisibility);
            if(argMode[1].find('s') != std::string::npos)
                pUser->setMode(silence);
            if(argMode[1].find('w') != std::string::npos && callUser->hasMode(userOper))
                pUser->setMode(wallopsOff);
        }
        else if (argMode[1][0] == '-'){
            if(argMode[1].find('o') != std::string::npos && callUser->hasMode(userOper))
                pUser->setMode(userOper);
            if(argMode[1].find('i') != std::string::npos)
                pUser->setMode(invisibility);
            if(argMode[1].find('s') != std::string::npos)
                pUser->setMode(silence);
            if(argMode[1].find('w') != std::string::npos && callUser->hasMode(userOper))
                pUser->setMode(wallopsOff);
        }
        else
            return ("MODE");
    }
    return (argMode[1]);
}


void UserService::mode(std::vector<std::string> request, int idUser) {
    std::vector<std::string>                argTarget;
    User*                                   pUser;
    if(!_users[idUser]->isAuthenticated())
        _postman->sendReply(idUser, ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if (request.size() > 2)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "MODE, you can't use ':',"));
    else if (request.size() == 1)
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(), "MODE"));
    else if ((argTarget = utils::splitBySpace(request[SECOND])).size() > 2 && argTarget.size() < 1)
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
        if(_users[idUser]->hasMode(userOper) || _users[idUser] == pUser){
            std::string bufMsg = changeMode(argTarget, _users[idUser], pUser);
            if(bufMsg == "MODE")
                _postman->sendReply(idUser, ERR_UMODEUNKNOWNFLAG(pUser->getFullname()));
            else if (bufMsg.find('o') && bufMsg[0] == '+'){
                addOper(pUser->getSocket());
                _postman->sendReply(idUser, RPL_MODE(_users[idUser]->getFullname(), pUser->getNickname(), argTarget[SECOND]));
            }
            else if (bufMsg.find('o') && bufMsg[0] == '-'){
                removeOper(pUser->getSocket());
                _postman->sendReply(idUser, RPL_MODE(_users[idUser]->getFullname(), pUser->getNickname(), argTarget[SECOND]));
            }
            else
                _postman->sendReply(idUser, RPL_MODE(_users[idUser]->getFullname(), pUser->getNickname(), argTarget[SECOND]));
        }
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