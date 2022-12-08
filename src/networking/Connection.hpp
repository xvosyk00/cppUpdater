//
// Created by pavel on 11/24/22.
//

#ifndef UPDATER_CONNECTION_HPP
#define UPDATER_CONNECTION_HPP

#include <string>

class Connection {
public:
    explicit Connection(int connectedSocketFd);
    Connection(const Connection&) = delete;
    Connection(Connection &&other) noexcept;
    Connection &operator=(Connection&) = delete;
    virtual void send(int value);
    virtual void send(const std::string &string);
    void send(const void *buffer, int size);
    virtual int receive();
    virtual void receive(std::string &string);
    virtual int receive(void *buffer, int size);
    Connection &operator<<(int value);
    Connection &operator<<(const std::string &value);
    Connection &operator>>(int &v);
    Connection &operator>>(std::string &v);
    virtual ~Connection();
private:
    int fd;
};


#endif //UPDATER_CONNECTION_HPP
