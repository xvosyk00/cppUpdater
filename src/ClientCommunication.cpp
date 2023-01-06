//
// Created by pavel on 11/29/22.
//

#include <iostream>
#include <utility>
#include "ClientCommunication.hpp"
#include "ServerConnector.hpp"
#include "ProtocolUtil.hpp"

ClientCommunication::ClientCommunication(Version version, std::string server, FileUpdater &fileUpdater, ServerConnector &serverConnector)
  : version(version),
    server(std::move(server)),
    fileUpdater(fileUpdater),
    serverConnector(serverConnector){
}

CheckResult ClientCommunication::checkVersion() const {
  auto connection = serverConnector.connect(server, port);
  *connection << ProtocolUtil::protocolVersion;
  Version latestVersion{};
  *connection >> latestVersion;
  *connection << "ok";
  CheckResult result{};
  result.serverHasNewerVersion = latestVersion > version;
  result.success = true;
  return result;
}

UpdateResult ClientCommunication::checkAndUpdate() const {
  auto connection = serverConnector.connect(server, port);
  *connection << ProtocolUtil::protocolVersion;
  Version latestVersion{};
  *connection >> latestVersion;
  bool serverHasNewerVersion = latestVersion > version;
  UpdateResult updateResult{};
  updateResult.success = true;
  updateResult.updated = false;
  if(serverHasNewerVersion){
    *connection << "update";
    update(*connection);
    updateResult.updated = true;
  }else{
    *connection << "ok";
  }
  return updateResult;

//  auto checkResult = checkVersion();
//  updateResult.success = checkResult.success;
//  updateResult.updated = false;
//  if(!checkResult.success)
//    return updateResult;
//  if(checkResult.serverHasNewerVersion){
//    updateResult.updated = update();
//  }
//  return updateResult;
}

void ClientCommunication::update(Connection &connection) const {
  connection << version;
  int filesNum;
  connection >> filesNum;
  std::string path;
  int action;
  for(; filesNum > 0; filesNum--) {
    connection >> path;
    connection >> action;
    if(action == static_cast<int>(ProtocolUtil::fileUpdateAction::Delete)){
      fileUpdater.deleteFile(path);
    }else if(action == static_cast<int>(ProtocolUtil::fileUpdateAction::Change)){
      int fileLen;
      connection >> fileLen;
      std::unique_ptr<char[]> fileContent(new char[fileLen]);
      connection.receive(fileContent.get(), fileLen); //todo this may not work for bigger files
      fileUpdater.changeFile(path, fileContent.get(), fileLen);
    }else{
      throw std::runtime_error("unrecognized action.");
    }
  }
}
