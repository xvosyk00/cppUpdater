//
// Created by pavel on 11/29/22.
//

#include "Version.hpp"

Version::Version() = default;

Version::Version(int v1, int v2, int v3) : v1(v1), v2(v2), v3(v3) {}

bool Version::operator<(const Version &rhs) const {
  if (v1 < rhs.v1)
    return true;
  if (rhs.v1 < v1)
    return false;
  if (v2 < rhs.v2)
    return true;
  if (rhs.v2 < v2)
    return false;
  return v3 < rhs.v3;
}

bool Version::operator>(const Version &rhs) const {
  return rhs < *this;
}

bool Version::operator<=(const Version &rhs) const {
  return !(rhs < *this);
}

bool Version::operator>=(const Version &rhs) const {
  return !(*this < rhs);
}

bool Version::operator==(const Version &rhs) const {
  return v3 == rhs.v3 && v2 == rhs.v2 && v1 == rhs.v1;
}

int Version::getV1() const {
  return v1;
}

int Version::getV2() const {
  return v2;
}

int Version::getV3() const {
  return v3;
}

Connection &operator<<(Connection &conn, const Version &version) {
  conn << version.v1 << version.v2 << version.v3;
  return conn;
}

Connection &operator>>(Connection &conn, Version &version) {
  conn >> version.v1 >> version.v2 >> version.v3;
  return conn;
}

std::ostream &operator<<(std::ostream &os, const Version &version) {
  os << version.v1 << "." << version.v2 << "." << version.v3 << ".";
  return os;
}

std::istream &operator>>(std::istream &is, Version &version) {
  is >> version.v1 >> version.v2 >> version.v3;
  return is;
}


