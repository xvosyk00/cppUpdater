//
// Created by pavel on 11/25/22.
//

#include "ConnectionListener.hpp"
#include <sys/socket.h>
#include <stdexcept>

ConnectionListener::ConnectionListener(int port) : port(port) {
  int opt = 1;
  if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    throw std::runtime_error("Socket creation error");
  }
  if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                 &opt, sizeof(opt))) {
    throw std::runtime_error("Setsockopt failed.");
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  if (bind(socketFd, (struct sockaddr*)&address,sizeof(address)) < 0) {
    throw std::runtime_error("Bind failed.");
  }
  if (::listen(socketFd, 3) < 0) {
    throw std::runtime_error("Listen failed.");
  }
}

Connection ConnectionListener::accept() {
  int new_socket;
  int addrLen = sizeof(address);
  if ((new_socket = ::accept(socketFd, (struct sockaddr*)&address,
  (socklen_t*)&addrLen)) < 0) {
    throw std::runtime_error("Accept failed.");
  }
  return Connection{new_socket};
}

ConnectionListener::~ConnectionListener() {
  shutdown(socketFd, SHUT_RDWR);
}

