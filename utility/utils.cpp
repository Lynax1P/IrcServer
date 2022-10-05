//
// Created by Chaos Sherill on 9/11/22.
//
#include "regex.h"
#include "utils.hpp"

std::vector<std::string> utils::splitCommand(std::string &request) {
    std::vector<std::string>    sumCommand;
    std::string                 temp = "";
    std::size_t                 pos;
    short                       countArg = 0;

    if (request.find('\n') != std::string::npos)
        request.erase(request.find('\n'));
    if (request.find('\r') != std::string::npos)
        request.erase(request.find('\r'));
    while(std::isspace(request[0]) && !request.empty())
        request.erase(0, 1);
    if ((pos = request.find(' ')) != std::string::npos)
    {
        temp = request.substr(0,pos);
        std::cout << "Arg " + std::to_string(++countArg) + ":"<< temp << std::endl;
        sumCommand.push_back(temp);
        request.erase(0, request.find(' '));
    }
    if ((pos = request.find(" :")) != std::string::npos)
    {
        temp = request.substr(0,pos);
        while(std::isspace(temp[0]) && !temp.empty())
            temp.erase(0, 1);
        if (temp.empty())
            std::cout << "empty"<<std::endl;
        else {
            sumCommand.push_back(temp);
            std::cout << "Arg " + std::to_string(++countArg) + ":"<< temp << std::endl;
        }
        request.erase(0, pos + 2);
        temp = request.substr(0);
        std::cout << "Arg " + std::to_string(++countArg) + ":"<< temp << std::endl;
        sumCommand.push_back(temp);
        request.erase(request.begin(), request.end());
    }
    else {
        while(std::isspace(request[0]) && !request.empty())
            request.erase(0, 1);
        std::cout << "Arg " + std::to_string(++countArg) + ":"<< request << std::endl;
        sumCommand.push_back(request);
    }
    return sumCommand;
}
