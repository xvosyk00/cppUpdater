//
// Created by pavel on 11/24/22.
//

#ifndef UPDATER_SERVERCONNECTOR_HPP
#define UPDATER_SERVERCONNECTOR_HPP


#include <string>
#include <memory>
#include "Connection.hpp"

class ServerConnector {
public:
    [[nodiscard]] virtual std::unique_ptr<Connection> connect(const std::string &hostname, int port) const = 0;
};


#endif //UPDATER_SERVERCONNECTOR_HPP
