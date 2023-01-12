//
// Created by pavel on 11/26/22.
//

#ifndef UPDATER_CLIENTDISPATCHER_HPP
#define UPDATER_CLIENTDISPATCHER_HPP


#include "ClientHandler.hpp"
#include "networking/ConnectionListener.hpp"
#include <mutex>

class ClientDispatcher {
public:
    explicit ClientDispatcher(ClientHandler &handler);
    [[noreturn]] void dispatch();
    void setMaxThreads(int maxThreads);
private:
    int maxThreads = 10;
    ClientHandler &handler;
    ConnectionListener listener;
    std::mutex m;
    int threadNumber = 0;
    void waitForSpareThreads();
};


#endif //UPDATER_CLIENTDISPATCHER_HPP
