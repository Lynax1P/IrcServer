//
// Created by Chaos Sherill on 9/11/22.
//

#ifndef IRC_UTILS_HPP
#define IRC_UTILS_HPP

#include "vector"
#include "map"
#include "iostream"
namespace utils{
    std::vector<std::string> splitCommand(std::string &request);
    std::vector<std::string> splitBySpace(std::string &request);
    std::vector<std::string> splitByChar(std::string &request, char c);
}


#endif //IRC_UTILS_HPP
