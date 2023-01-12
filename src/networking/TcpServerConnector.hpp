//
// Created by pavel on 1/6/23.
//

#ifndef UPDATER_TCPSERVERCONNECTOR_HPP
#define UPDATER_TCPSERVERCONNECTOR_HPP


#include "../ServerConnector.hpp"

class TcpServerConnector : public ServerConnector {
public:
    std::unique_ptr<Connection> connect(const std::string &hostname, int port) const override;
};


#endif //UPDATER_TCPSERVERCONNECTOR_HPP
