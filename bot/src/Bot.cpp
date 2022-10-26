//
// Created by Chaos Sherill on 10/26/22.
//

#include "Bot.hpp"

void Bot::error(std::string msg) {
    std::cout << msg;
    exit(1);
}

Bot::Bot(std::string hostname, std::string port, std::string pass): _name("bot"), _hostname(hostname), _port(port), _pass(pass), _isAuth(false){
    int iPort = std::stoi(_port);
    if (1024 > iPort || iPort > 65535)
        error("Port rang [1024, 65535]");
    hostent *host = NULL;
    if ((host = gethostbyname(_hostname.c_str())) == NULL)
        error("incorrect hostname");
    std::vector<std::string> splitHostAddr = utils::splitByChar(hostname,'.');
    sockaddr_in addressHost = {0, AF_INET, \
                        htons(std::stoi(_port)), {0},{}};
    if(inet_aton(host->h_name, &addressHost.sin_addr) == 0)
        error("Incorrect ip address has been passed");
    if((_socket = socket(addressHost.sin_family, SOCK_STREAM, 0)) == -1)
        error("Socket Error");
    if(connect(_socket, (sockaddr*)&addressHost, sizeof(sockaddr)) == -1)
        error("Connect error");
}

Bot::~Bot() {
    std::cout << "bye\n";
    close(_socket);
}

bool Bot::hasRequest() {
    return (!_request.empty() &&
            _request.find('\n') != std::string::npos);
}

std::string Bot::getRequest() {
    std::string::size_type  index = _request.find('\n') + 1;
    std::string             request = _request.substr(0,index);
    _request.erase(0, index);
    return request;
}

void Bot::sendReceive() {
    char buf[128];

    bzero(&buf,128);
    if(recv(_socket,&buf, 127, 0) > 0)
        _request += buf;
    else
        throw("error");
}

void  Bot::sendBack()
{
    if(!(_reply.empty())){
        send(_socket, _reply.c_str(), _reply.length(), 0);
        _reply.clear();
    }
}

void Bot::resetPass() {
    if (_isAuth == true)
        return;
    static int tries = 3;
    if (tries < 0){
        std::cout << "error: authentication failed.";
        throw ("end");
    }
    std::cout << "You wrote a wrong password, try again.\n";
    std::cin >> _pass;
    std::cout << "You written a new password : " << _pass << ". Let's try it.\n";
    _request.clear();
    _reply = RPL_PASS(_pass) + RPL_NICK(_name) + "USER bot me loc :IamBOT \r\n";
    tries--;
}

void Bot::sendMem(std::string request) {
    int                         count = 0;
    std::ifstream               inFile("src/mem/list");
    std::vector<std::string>    fileName;
    std::string                 bufString;

    if (inFile.fail())
        return;
    std::string::size_type find = request.find(':') + 1;
    request.erase(0, find);
    std::string name = request.substr(0,request.find(' '));
    std::cout << "Send >> " + name;
    std::srand(std::time(NULL));
    inFile >> count;
    for(;count;--count){
        if(!(getline(inFile,bufString))){
            break;
        }
        fileName.push_back(bufString);
    }
    inFile.close();
    bufString = fileName[rand() % fileName.size() - 1];
    std::ifstream fileMem(bufString.c_str());
    if((fileMem.fail()))
        return;
    for(; getline(fileMem, bufString);){
        _reply += "PRIVMSG " + name + " :" + bufString + "\r\n";
    }
}

void Bot::sendProcessed() {
    while (hasRequest())
    {
        std::string request = getRequest();
        std::cout << request;
        if(request.find("PRIVMSG") != std::string::npos || request.find("NOTICE") != std::string::npos ) {
            if ((request.find("mem") != std::string::npos) || (request.find("мем") != std::string::npos)) {
                sendMem(request);
            }
        }
        else if (request.find(":ircserv 375 bot :- Message of the day -") != std::string::npos)
            _isAuth = true;
        else if (request.find(":ircserv 451 * :You have not registered") != std::string::npos ||\
                    _request.find("You may not reregister") != std::string::npos ||\
                    _request.find(":ircserv 464 * :Password incorrect") != std::string::npos){
            resetPass();
        }
    }
}

void Bot::run() {
    _reply = RPL_PASS(_pass) + RPL_NICK(_name) + "USER bot me loc :IamBOT \r\n";
    while(true)
    {
        sendBack();
        sendReceive();
        sendProcessed();
    }
}