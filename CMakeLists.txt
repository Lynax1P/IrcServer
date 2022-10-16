cmake_minimum_required(VERSION 3.16.3)
project(Irc)

set(CMAKE_CXX_STANDARD 98)


add_executable(Irc

        t.cpp
        Postman.cpp
        Server.cpp
        UserService.cpp
        User.cpp
        Channel.cpp
        utility/utils.cpp
        command/pass.cpp
        command/privmsg.cpp
        command/user.cpp
        command/nick.cpp
        command/away.cpp
        command/pong.cpp
        command/join.cpp
        command/names.cpp
        command/part.cpp
        command/invite.cpp
        command/kick.cpp
        command/quit.cpp
        command/topic.cpp
        command/notice.cpp
        command/list.cpp
        command/ison.cpp
        command/oper.cpp
        command/wallops.cpp
        )
