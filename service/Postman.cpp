//
// Created by Chaos Sherill on 9/3/22.
//

#include "Postman.hpp"

std::string Postman::getRequest(int userId) {
    std::string::size_type indexUser = _requests.at(userId).find('\n') + 1;
    std::string            request = _requests.at(userId).substr(0, indexUser);
    _requests[userId].erase(0,indexUser);
    return request;
}

std::string Postman::getReply(int userId) {
    std::string     reply = _replies.at(userId);
    clearReply(userId);
    return reply;
}

void Postman::sendRequest(int userId, const std::string &request) {
    _requests[userId] += request;
}

void Postman::sendReply(int userId, const std::string &reply) {
    _replies[userId] += reply;
    _replies[userId] += "\r\n";
}

bool Postman::hasRequest(int userId) const {
    return (_requests.find(userId) != _requests.end() &&
            !_requests.at(userId).empty() &&
            _requests.at(userId).find('\n') != std::string::npos);
}

bool Postman::hasReply(int userId) const {
    return (_replies.find(userId) != _replies.end() && !_replies.at(userId).empty());
}

void Postman::clearRequest(int userId) {
    _requests[userId].clear();
}

void Postman::clearReply(int userId) {
    _replies[userId].clear();
}

void Postman::clear(int userId) {
    _replies[userId].clear();
    _requests[userId].clear();
}