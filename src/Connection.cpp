//
// Created by pavel on 11/24/22.
//

#include "Connection.hpp"

Connection &Connection::operator<<(int value) {
  send(value);
  return *this;
}

Connection &Connection::operator>>(int &v) {
  v = receive();
  return *this;
}

Connection &Connection::operator>>(std::string &v) {
  receive(v);
  return *this;
}

Connection &Connection::operator<<(const std::string &value) {
  send(value);
  return *this;
}