//
// Created by pavel on 11/24/22.
//

#ifndef UPDATER_CONNECTION_HPP
#define UPDATER_CONNECTION_HPP

#include <string>

class Connection {
public:
    virtual void send(int value) = 0;
    virtual void send(const std::string &string) = 0;
    virtual void send(const void *buffer, int size) = 0;
    virtual int receive() = 0;
    virtual void receive(std::string &string) = 0;
    virtual int receive(void *buffer, int size) = 0;
    virtual Connection &operator<<(int value);
    virtual Connection &operator<<(const std::string &value);
    virtual Connection &operator>>(int &v);
    virtual Connection &operator>>(std::string &v);
    virtual ~Connection() = default;
};


#endif //UPDATER_CONNECTION_HPP
