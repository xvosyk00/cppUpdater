//
// Created by pavel on 11/25/22.
//

#ifndef UPDATER_CLIENTHANDLER_HPP
#define UPDATER_CLIENTHANDLER_HPP


#include "Connection.hpp"

class ClientHandler {
public:
    virtual void handle(Connection &conn) = 0;
};


#endif //UPDATER_CLIENTHANDLER_HPP
