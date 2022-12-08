//
// Created by pavel on 11/27/22.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/networking/Connection.hpp"
#include "../src/ServerCommunication.hpp"
#include "../src/ProtocolUtil.hpp"
#include "../src/ClientCommunication.hpp"
#include "../src/networking/ServerConnector.hpp"
#include "Mocks.hpp"

class ConnectionMock : public Connection{
public:
    ConnectionMock() : Connection(-1) {};
    MOCK_METHOD(void, send, (int value), (override));
    MOCK_METHOD(void, send, (const std::string &value), (override));
//    MOCK_METHOD(void, send, (const void *buffer, int size), (override));
    MOCK_METHOD(int, receive, (), (override));
    MOCK_METHOD(void, receive, (std::string &v), (override));
    MOCK_METHOD(int, receive, (void *buffer, int size), (override));
};


TEST(protocolTest, ServerCheckVersion){
  ConnectionMock mock;
  testing::InSequence seq;
  EXPECT_CALL(mock, receive(_))
    .WillOnce([](std::string &v){v = ProtocolUtil::protocolVersion; });
  EXPECT_CALL(mock, send((int)0));
  EXPECT_CALL(mock, send((int)0));
  EXPECT_CALL(mock, send(1));
  EXPECT_CALL(mock, receive(_))
    .WillOnce([](std::string &v){v = "ok"; });

  VersionDb db{std::stringstream{"0 0 1 0"}};
  ServerCommunication sc(db);
  sc.handle(mock);
}

TEST(protocolTest, ClientCheckVersion){
  auto mock = std::make_unique<ConnectionMock>();
  testing::InSequence seq;
  EXPECT_CALL(*mock, send(ProtocolUtil::protocolVersion));
  EXPECT_CALL(*mock, receive())
    .WillOnce(Return(0))
    .WillOnce(Return(0))
    .WillOnce(Return(1));
  EXPECT_CALL(*mock, send("ok"));
  ServerConnector serverConnector;
  serverConnector.setConnectionMock(std::move(mock));
  FileUpdaterMock fileUpdaterMock{};

  ClientCommunication(Version{0,0,1}, "localhost", fileUpdaterMock, serverConnector).checkVersion();
}

TEST(protocolTest, ClientUpdateDeleteFile) {
  auto mock = std::make_unique<ConnectionMock>();
  FileUpdaterMock fileUpdaterMock{};
  testing::InSequence seq;
  EXPECT_CALL(*mock, send(ProtocolUtil::protocolVersion));
  EXPECT_CALL(*mock, receive())
    .WillOnce(Return(0))
    .WillOnce(Return(0))
    .WillOnce(Return(2));
  EXPECT_CALL(*mock, send("update"));
  EXPECT_CALL(*mock, send((int)0));
  EXPECT_CALL(*mock, send((int)0));
  EXPECT_CALL(*mock, send(1));
  EXPECT_CALL(*mock, receive())
    .WillOnce(Return(1));
  EXPECT_CALL(*mock, receive(_))
    .WillOnce([](std::string &v){v = "file1"; });
  EXPECT_CALL(*mock, receive())
    .WillOnce(Return(static_cast<int>(ProtocolUtil::fileUpdateAction::Delete)));

  ServerConnector serverConnector;
  serverConnector.setConnectionMock(std::move(mock));
  EXPECT_CALL(fileUpdaterMock, deleteFile("file1"));

  ClientCommunication(Version{0,0,1}, "localhost", fileUpdaterMock, serverConnector).checkAndUpdate();
}

TEST(protocolTest, ClientUpdateChangeFile) {
  auto mock = std::make_unique<ConnectionMock>();
  FileUpdaterMock fileUpdaterMock{};
  testing::InSequence seq;
  EXPECT_CALL(*mock, send(ProtocolUtil::protocolVersion));
  EXPECT_CALL(*mock, receive())
    .WillOnce(Return(0))
    .WillOnce(Return(0))
    .WillOnce(Return(2));
  EXPECT_CALL(*mock, send("update"));
  EXPECT_CALL(*mock, send((int)0));
  EXPECT_CALL(*mock, send((int)0));
  EXPECT_CALL(*mock, send(1));
  EXPECT_CALL(*mock, receive())
    .WillOnce(Return(1));
  EXPECT_CALL(*mock, receive(_))
    .WillOnce([](std::string &v){v = "file1"; });
  EXPECT_CALL(*mock, receive())
    .WillOnce(Return(static_cast<int>(ProtocolUtil::fileUpdateAction::Change)));
  EXPECT_CALL(*mock, receive())
    .WillOnce(Return(12));
  EXPECT_CALL(*mock, receive(_, _))
    .WillOnce([](void *buffer, int size){ strcpy(static_cast<char*>(buffer), "filecontent"); return 12; });

  ServerConnector serverConnector;
  serverConnector.setConnectionMock(std::move(mock));
  EXPECT_CALL(fileUpdaterMock, changeFile("file1", _, 12))
    .WillOnce([](const std::string &file, const char *content, int length){ EXPECT_STREQ(content, "filecontent");});

  ClientCommunication(Version{0,0,1}, "localhost", fileUpdaterMock, serverConnector).checkAndUpdate();
}
