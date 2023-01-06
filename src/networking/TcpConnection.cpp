//
// Created by pavel on 1/6/23.
//

#include "TcpConnection.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <unistd.h>

TcpConnection::TcpConnection(int fd) : fd(fd) {
}

TcpConnection::~TcpConnection() {
  if(fd >= 0)
    ::close(fd);
}

TcpConnection::TcpConnection(TcpConnection &&other)  noexcept : fd(other.fd){
  other.fd = -1;
}

int TcpConnection::receive(void *buffer, int size) {
  int count = recv(fd, buffer, size, 0);
  if(count < 0)
    throw std::runtime_error("Recv error.");
  return count;
}

void TcpConnection::send(const void *buffer, int size) {
  if(::send(fd, buffer, size, 0) < 0){
    throw std::runtime_error("send failed");
  }
}

void TcpConnection::send(int value) {
  uint32_t buff = htonl(value);
  send(&buff, sizeof(buff));
}

int TcpConnection::receive() {
  const int intSize = sizeof(uint32_t);
  union {
      char arr[intSize];
      uint32_t val;
  }buff;
  int received = 0;
  do {
    int r = receive(&buff.arr[received], intSize - received);
    if(r == 0)
      throw std::runtime_error("Integer not received.");
    received += r;
  } while (received < intSize);
  return ntohl(buff.val);
}

void TcpConnection::receive(std::string &string) {
  const int buffSize = 81;
  char buff[buffSize];
  int strLen = 0;
  do{
    receive(&buff[strLen], 1);
    strLen++;
    if(strLen >= buffSize)
      throw std::runtime_error("Received string is too long.");
  } while (buff[strLen - 1] != 0);
  string.assign(buff, strLen - 1);
}

void TcpConnection::send(const std::string &value) {
  send(value.c_str(), value.size() + 1); //sending string including null termination
}

