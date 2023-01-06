//
// Created by pavel on 12/7/22.
//

#ifndef UPDATER_MOCKS_HPP
#define UPDATER_MOCKS_HPP

#include "gmock/gmock.h"
#include "../src/filesystem/FileUpdater.hpp"

using ::testing::Matcher;
using ::testing::Return;
using ::testing::_;

class FileUpdaterMock : public FileUpdater {
public:
    MOCK_METHOD(void, deleteFile, (const std::string &file), (override, const));
    MOCK_METHOD(void, changeFile, (const std::string &file, const char *content, int length), (override, const));
};

//this is not mock class to simplify use
class ServerConnectorStub : public ServerConnector {
    mutable std::unique_ptr<Connection> mockConnection;
    mutable bool called = false;
public:
    explicit ServerConnectorStub(std::unique_ptr<Connection> mockConnection) : mockConnection(std::move(mockConnection)) {}
    [[nodiscard]] std::unique_ptr<Connection> connect(const std::string &hostname, int port) const override {
      if(called)
        throw std::runtime_error("ServerConnectorStub::Connect was called twice.");
      called = true;
      return std::move(mockConnection);
    };
};
#endif //UPDATER_MOCKS_HPP
