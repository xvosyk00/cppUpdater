//
// Created by pavel on 11/28/22.
//

#include <fstream>
#include "ServerCommunication.hpp"
#include "ProtocolUtil.hpp"
#include <filesystem>

ServerCommunication::ServerCommunication(VersionDb &versionDb) : versionDb(versionDb) {}

void ServerCommunication::handle(Connection &conn) {
  std::string buff;
  conn >> buff;
  if(buff != ProtocolUtil::protocolVersion) //by this client signals currentVersion of protocol used
    return;
  auto& latestVersion = versionDb.getVersion();
  conn << latestVersion;
  conn >> buff;
  if(buff == "ok") //client can decide to end connection (ok) or update
    return;
  if(buff != "update")
    return;
  Version clientVersion;
  conn >> clientVersion;
  auto& changes = versionDb.getChanges(clientVersion);
  conn << static_cast<int>(changes.size());
  for(auto& c : changes){
    conn << c.filename;
    conn << static_cast<int>(c.action);
    if(c.action == ProtocolUtil::fileUpdateAction::Change){
      int filesize = std::filesystem::file_size(c.filename);
      conn << filesize;
      std::ifstream fileHandle(c.filename, std::ios::binary);
      char *content = new char[filesize + 1];
      fileHandle.get(content, filesize + 1); //get counts zero termination as character too
      conn.send(content, filesize);
    }
  }
}
