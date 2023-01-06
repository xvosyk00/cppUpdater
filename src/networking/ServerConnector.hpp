//
// Created by pavel on 11/24/22.
//

#ifndef UPDATER_SERVERCONNECTOR_HPP
#define UPDATER_SERVERCONNECTOR_HPP


#include <string>
#include <memory>
#include "../Connection.hpp"

class ServerConnector {
    std::unique_ptr<Connection> connMock;
public:
    [[nodiscard]] std::unique_ptr<Connection> connect(const std::string &hostname, int port);
    void setConnectionMock(std::unique_ptr<Connection> connection);
};


#endif //UPDATER_SERVERCONNECTOR_HPP
