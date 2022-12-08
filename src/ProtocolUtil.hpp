//
// Created by pavel on 11/28/22.
//

#ifndef UPDATER_PROTOCOLUTIL_HPP
#define UPDATER_PROTOCOLUTIL_HPP


#include <string>

class ProtocolUtil {
public:
  static const std::string protocolVersion;
  static const int port;
  enum class fileUpdateAction{ Delete = 0, Change = 1};
};


#endif //UPDATER_PROTOCOLUTIL_HPP
