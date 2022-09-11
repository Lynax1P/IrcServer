//
// Created by Chaos Sherill on 9/11/22.
//

#include "utils.hpp"

std::vector<std::string> utils::splitCommand(std::string &request) {

    if(request.find('\n') != std::string::npos)
        request.erase(request.find('\n'));
    if(request.find('\r') != std::string::npos)
        request.erase(request.find('\r'));

}
