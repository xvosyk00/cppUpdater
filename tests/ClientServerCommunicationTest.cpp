//
// Created by pavel on 12/7/22.
//

/**
 * This file contains tests of both client use cases.
 * checkVersion and checkAndUpdate methods.
 * Whole system is tested because client is communicating with server through localhost socket.
 */

#include <thread>
#include <fstream>
#include "gtest/gtest.h"
#include "../src/ServerCommunication.hpp"
#include "../src/networking/ConnectionListener.hpp"
#include "../src/ClientCommunication.hpp"
#include "Mocks.hpp"
#include "../src/networking/TcpServerConnector.hpp"

static const int port = 5050;

class ClientServerCommunicationTest : public ::testing::Test {
protected:
    ConnectionListener connectionListener{port};
    std::unique_ptr<ClientCommunication> clientCommunication;

    ClientCommunication &makeClient(Version v) {
      clientCommunication = std::unique_ptr<ClientCommunication>(new ClientCommunication{v, "localhost", fileUpdaterMock, serverConnector});
      return *clientCommunication;
    }

    void runServer(std::string &&dbFile){
      auto serverCommunication = makeServerHandler(dbFile);
      std::thread t([&, serverCommunication] () mutable{
          auto conn = connectionListener.accept();
          serverCommunication.handle(*conn);
      });
      t.detach();
    }
    ServerCommunication makeServerHandler(std::string &dbFile){
      versionDb = std::make_unique<VersionDb>(std::stringstream (dbFile));
      return ServerCommunication{*versionDb};
    }
    FileUpdaterMock fileUpdaterMock;
    TcpServerConnector serverConnector;
    std::unique_ptr<VersionDb> versionDb;
};

TEST_F(ClientServerCommunicationTest, versionCheck_sameVersion)
{
  runServer("2 3 4 0");
  auto result = makeClient({2,3,4}).checkVersion();
  ASSERT_TRUE(result.success);
  ASSERT_FALSE(result.serverHasNewerVersion);
}

TEST_F(ClientServerCommunicationTest, versionCheck_olderVersion)
{
  runServer("2 3 4 0");
  auto result = makeClient({2,3,3}).checkVersion();
  ASSERT_TRUE(result.success);
  ASSERT_TRUE(result.serverHasNewerVersion);
}

TEST_F(ClientServerCommunicationTest, versionCheck_newerVersion)
{
  runServer("2 3 4 0");
  auto result = makeClient({2,3,5}).checkVersion();
  ASSERT_TRUE(result.success);
  ASSERT_FALSE(result.serverHasNewerVersion);
}

TEST_F(ClientServerCommunicationTest, checkAndUpdate_noUpdateNeeded){
  runServer("2 3 4   1 file1 0");
  auto result = makeClient({2,3,4}).checkAndUpdate();
  ASSERT_TRUE(result.success);
  ASSERT_FALSE(result.updated);
}

TEST_F(ClientServerCommunicationTest, checkAndUpdate_fromZero){
  EXPECT_CALL(fileUpdaterMock, deleteFile("file1"));
  runServer("2 3 4   1 file1 0");
  auto result = makeClient({0,0,0}).checkAndUpdate();
  ASSERT_TRUE(result.success);
  ASSERT_TRUE(result.updated);
}

TEST_F(ClientServerCommunicationTest, checkAndUpdate_fromPreviousVersion){
  EXPECT_CALL(fileUpdaterMock, deleteFile("file1"));
  runServer("0 0 1 1 file2 0\n  2 3 4   1 file1 0");
  auto result = makeClient({0,0,1}).checkAndUpdate();
  ASSERT_TRUE(result.success);
  ASSERT_TRUE(result.updated);
}

TEST_F(ClientServerCommunicationTest, checkAndUpdate_multipleVersionsBehind){
  EXPECT_CALL(fileUpdaterMock, deleteFile("file1"));
  EXPECT_CALL(fileUpdaterMock, deleteFile("file2"));
  EXPECT_CALL(fileUpdaterMock, deleteFile("file3"));
  runServer("0 0 1 1 file4 0\n"
            "0 0 2 1 file3 0\n"
            "0 0 3 1 file2 0\n"
            "0 0 4 1 file1 0");
  auto result = makeClient({0,0,1}).checkAndUpdate();
  ASSERT_TRUE(result.success);
  ASSERT_TRUE(result.updated);
}

TEST_F(ClientServerCommunicationTest, checkAndUpdate_downloadFile){
  const char *testFile1 = "/tmp/updaterTestFile1";
  const std::string content1 = "contentOfFile1";
  std::ofstream file1(testFile1);
  file1 << content1;
  file1.close();
  EXPECT_CALL(fileUpdaterMock, changeFile(testing::StrEq(testFile1), testing::StrEq(content1.c_str()), content1.size()));
  runServer("2 3 4   1 /tmp/updaterTestFile1 1");
  auto result = makeClient({0,0,0}).checkAndUpdate();
  ASSERT_TRUE(result.success);
  ASSERT_TRUE(result.updated);
}
