//
// Created by pavel on 11/26/22.
//

#include "ClientDispatcher.hpp"
#include <thread>
#include <iostream>

ClientDispatcher::ClientDispatcher(ClientHandler &handler) : handler(handler), listener(5050) {

}

[[noreturn]] void ClientDispatcher::dispatch() {
  while(true){
    auto conn = listener.accept();
    std::thread t{[&, conn = std::move(conn)] () mutable{
        {
          const std::lock_guard l{m};
          threadNumber++;
        }
        try{
          handler.handle(*conn);
        }catch (std::runtime_error &e){
          //log error?
        }
        {
          const std::lock_guard l{m};
          threadNumber--;
        }
    }};
    t.detach();
    waitForSpareThreads();
  }
}

void ClientDispatcher::waitForSpareThreads() {
  while(true) {
    {
      const std::lock_guard l{m};
      if (threadNumber < maxThreads) {
        break;
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds (1));
  }
}

void ClientDispatcher::setMaxThreads(int maxThreads) {
  ClientDispatcher::maxThreads = maxThreads;
}
