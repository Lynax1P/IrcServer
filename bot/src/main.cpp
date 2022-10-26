//
// Created by Chaos Sherill on 10/26/22.
//
#include "Bot.hpp"

int main(int argc, char **argv)
{
    if (argc != 4){
        std::cerr << "Error :<" << argv[0] << "> <hostname> <port> <pass>";
        return (1);
    }
    Bot     bot(argv[1],argv[2],argv[3]);
    try{
        bot.run();
    }
    catch (...){}
    return (0);
}