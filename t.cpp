//
// Created by Nina on 06.09.2022.
//
#include "iostream"
#include "string"
#include "Server.hpp"
#include "utility/utils.hpp"
int main(int argc,char** argv){
    if(argc != 3)
    {
        std::cerr << "./<NAME> <PORT> <PASS>\n";
        exit(EXIT_FAILURE);
    }
    else if (strtol(argv[1], nullptr, 10) <= 1024
                || strtol(argv[1], nullptr, 10) > 65535)
    {
        std::cerr << "PORT ERROR";
        exit(EXIT_FAILURE);
    }

    Server  _server(argv[1],argv[2]);
    _server.startPrimary();

//    std::string args = "      s       PASS :fssfssf";
//    std::vector<std::string>    argumentsVec = utils::splitCommand(args);
//    if(argumentsVec[0].find("PASS") != std::string::npos)
//        std::cout << argumentsVec[0] << "\n";
//    std::cout << argumentsVec[1] << "\n";
//    std::cout << argumentsVec[2] << "\n";

}