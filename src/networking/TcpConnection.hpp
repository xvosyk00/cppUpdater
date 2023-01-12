//
// Created by pavel on 1/6/23.
//

#ifndef UPDATER_TCPCONNECTION_HPP
#define UPDATER_TCPCONNECTION_HPP


#include "../Connection.hpp"

class TcpConnection : public Connection {
public:
    explicit TcpConnection(int connectedSocketFd);
    TcpConnection(const TcpConnection&) = delete;
    TcpConnection(TcpConnection &&other) noexcept;
    TcpConnection &operator=(TcpConnection&) = delete;
    void send(int value) override;
    void send(const std::string &string) override;
    void send(const void *buffer, int size) override;
    int receive() override;
    void receive(std::string &string) override;
    int receive(void *buffer, int size) override;
    ~TcpConnection() override;
private:
    int fd;
};


#endif //UPDATER_TCPCONNECTION_HPP
