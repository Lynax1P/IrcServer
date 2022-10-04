//
// Created by Chaos Sherill on 9/11/22.
//
#include "regex.h"
#include "utils.hpp"

std::vector<std::string> utils::splitCommand(std::string &request) {
    std::vector<std::string>    sumCommand;
    std::string                 temp = "";
    std::size_t                 pos;

    if(request.find('\n') != std::string::npos)
        request.erase(request.find('\n'));
    if(request.find('\r') != std::string::npos)
        request.erase(request.find('\r'));
    while(!isalpha(request[0])){
        request.erase(0, 1);
        if(request.empty()){
            break;
        }
    }
    if(request.find(' ') != std::string::npos)
    {
        pos  = request.find(' ');
        temp = request.substr(0,pos);
        std::cout << temp;
        sumCommand.push_back(temp);
        request.erase(0, request.find(' ')+1);
    }
    if(request.find(":") != std::string::npos)
    {
        pos = request.find(":");
        temp = request.substr(0,pos);
        std::cout << " |* \" :\"|"<< temp<< '|';
        sumCommand.push_back(temp);
        temp = request.substr(pos+1);
        std::cout << "\" :\" *"<< temp<<std::endl;
        sumCommand.push_back(temp);
        request.erase(request.begin()+pos, request.end());
    }
    else{
        sumCommand.push_back(request);
    }
    return sumCommand;
}
