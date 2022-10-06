cmake_minimum_required(VERSION 3.16.3)
project(Irc)

set(CMAKE_CXX_STANDARD 98)

add_executable(Irc
        t.cpp
        Postman.cpp
        Server.cpp
        UserService.cpp
        User.cpp
        utility/utils.cpp
        command/pass.cpp
        command/privmsg.cpp
        command/user.cpp
        command/nick.cpp)
