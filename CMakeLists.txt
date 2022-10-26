cmake_minimum_required(VERSION 3.16.3)
project(Irc)

set(CMAKE_CXX_STANDARD 98)


add_executable(Irc

        application/main.cpp
        service/Postman.cpp
        application/Server.cpp
        service/UserService.cpp
        clients/User.cpp
        clients/Channel.cpp
        service/utility/utils.cpp
        service/command/pass.cpp
        service/command/privmsg.cpp
        service/command/userc.cpp
        service/command/nick.cpp
        service/command/away.cpp
        service/command/pong.cpp
        service/command/join.cpp
        service/command/names.cpp
        service/command/part.cpp
        service/command/invite.cpp
        service/command/kick.cpp
        service/command/quit.cpp
        service/command/topic.cpp
        service/command/notice.cpp
        service/command/list.cpp
        service/command/ison.cpp
        service/command/oper.cpp
        service/command/wallops.cpp
        service/command/mode.cpp
        )
