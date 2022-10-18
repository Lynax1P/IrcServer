//
// Created by Chaos Sherill on 9/11/22.
//

#ifndef IRC_UTILS_HPP
#define IRC_UTILS_HPP

#include "vector"
#include "map"
#include "iostream"
namespace utils{
    std::vector<std::string>    splitCommand(std::string &request);
    std::vector<std::string>    splitBySpace(std::string &request);
    std::vector<std::string>    splitByChar(std::string &request, char c);
    bool                        isValidChannelMode(std::string &arguments);
    bool                        isValidUserMode(std::string &arguments);
}


#endif //IRC_UTILS_HPP
