# IrcServer
**An Internet Relay Chat server in C++ 98 based on rfc1459 standard.  
Сервер на базе IRC протокола для обмена сообщениями.**

<img src="https://www.plutora.com/wp-content/uploads/2018/11/irc_internet_relay_chat.png" width="300"  alt="channel"/>

### Supported clients :
- Netcat 
  ` nc localhost [port]`
- LimeChat
- Adium

## How to run
Use **make** rule to compile the program. Run it with port and password
``` 
make && ./ircserv [port] [password]
``` 


Bot running
```
cd Sources/bot && make
```
```
./bot 0.0.0.0 [port] [password]
```
