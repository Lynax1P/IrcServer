//
// Created by Chaos Sherill on 10/6/22.
//

#include "../UserService.hpp"

static bool isValidNick(std::string nickname){
    std::string     allowCharacter = "-[]^{}";
    for(std::string::size_type i = 0; i != nickname.length(); ++i)
        if(std::isalnum(nickname[i]) && allowCharacter.find(nickname[i]) == std::string::npos)
            return false;
    return true;
}

void UserService::nick(std::vector<std::string> request, int idUser) {
    if(!_users[idUser]->isRegistred())
        _postman->sendReply(idUser,
                            ERR_NOTREGISTERED(_users[idUser]->getNickname()));
    else if(request.size() < 2)
        _postman->sendReply(idUser,
                            ERR_NONICKNAMEGIVEN(_users[idUser]->getNickname()));
    else if (request[SECOND].length() > 9 &&
                isValidNick(request[SECOND]))
        _postman->sendReply(idUser,
                            ERR_ERRONEUSNICKNAME(_users[idUser]->getNickname(), request[SECOND]));
    else if (findUserByNickname(request[SECOND]) != nullptr)
        _postman->sendReply(idUser,
                            ERR_NICKNAMEINUSE(_users[idUser]->getNickname(), request[SECOND]));
    else
    {
        if(!_users[idUser]->isAuthenticated() && !(_users[idUser]->getUsername().empty()))
        {
            _users[idUser]->setNickname(request[SECOND]);
            welcomeUser(idUser);
        }
        else
            _users[idUser]->setNickname(request[SECOND]);
    }
}
