//
// Created by pavel on 11/25/22.
//

#ifndef UPDATER_CONNECTIONLISTENER_HPP
#define UPDATER_CONNECTIONLISTENER_HPP

#include "Connection.hpp"
#include "../ClientHandler.hpp"
#include <netinet/in.h>

class ConnectionListener {
public:
    explicit ConnectionListener(int port);
    Connection accept();
    ~ConnectionListener();
private:
    int port;
    int socketFd;
    sockaddr_in address{};
};


#endif //UPDATER_CONNECTIONLISTENER_HPP
