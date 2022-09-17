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
    while(isalpha(request[0]) || request.empty())
        request.erase(request[0]);
    if(request.empty())
    {
        sumCommand[0] = nullptr;
        return sumCommand;
    }
    if(request.find(' ') != std::string::npos)
    {
        pos  = request.find(' ') - 1;
        temp = request.substr(0,pos);
        sumCommand[0] += temp;
        request.erase(0, request.find(' '));
    }
    if(request.find(':') != std::string::npos)
    {
        pos = request.find(':');
        temp = request.substr(0,pos - 1);
        sumCommand[1] += temp;
        temp = request.substr(pos);
        sumCommand[2] += temp;
        request.erase(request.begin()+pos, request.end());
    }
    else
        sumCommand[1] += request.substr(0);
    return sumCommand;
}
