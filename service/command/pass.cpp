//
// Created by Chaos Sherill on 10/4/22.
//

#include "../UserService.hpp"

void UserService::pass(std::vector<std::string> request, int idUser) {
    if (_users[idUser]->isRegistred())
        _postman->sendReply(idUser, ERR_ALREADYREGISTRED(_users[idUser]->getNickname()));
    else if(request.size() != 2){
        _postman->sendReply(idUser, ERR_NEEDMOREPARAMS(_users[idUser]->getNickname(),"PASS"));
        std::cout << "|"<< request.size()<< "|" << std::endl;
    }
    else
    {
        if (std::equal(request[request.size()-1].begin(), request[request.size()-1].end(), _password.c_str()))
            _users[idUser]->setRegistred(true);
        else
            _postman->sendReply(idUser,ERR_PASSWDMISMATCH(_users[idUser]->getNickname()));
    }
}