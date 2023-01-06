//
// Created by pavel on 11/24/22.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/ServerConnector.hpp"
#include "../src/networking/ConnectionListener.hpp"
#include "../src/ClientDispatcher.hpp"
#include "../src/networking/TcpServerConnector.hpp"
#include <thread>

using ::testing::_;

class HandlerMock : public ClientHandler{
public:
    MOCK_METHOD(void, handle, (Connection &conn), (override));
};

const std::string localhost = "localhost";
const int port = 5050;

TEST(connectionTest, connectToServer){
  auto msg = "hello world\n";
  std::thread t([&](){
      auto conn = TcpServerConnector().connect(localhost, port);
      conn->send(msg, strlen(msg) + 1);
  });
//  HandlerMock m{};
//  EXPECT_CALL(m, handle(_)).Times(1).WillRepeatedly([&](Connection c){
//    char buff[50];
//    c.receive(buff, 49);
//    ASSERT_STREQ(buff, msg);
//  });
  ConnectionListener l(port);
  auto conn = l.accept();
  char buff[50];
  conn->receive(buff, 49);
  ASSERT_STREQ(buff, msg);
  t.join();
}

TEST(connectionTest, sendInt){
  std::thread t([&](){
      auto conn = TcpServerConnector().connect(localhost, port);
      *conn << 2;
  });
  ConnectionListener l(port);
  auto conn = l.accept();
  int v;
  *conn >> v;
  ASSERT_EQ(v, 2);
  t.join();
}

//class DummyHandler : public ClientHandler{
//    void handle(Connection connMock) override {
//      auto msg = "hello world\n";
//      char buff[50];
//      connMock.receive(buff, 49);
//      ASSERT_STREQ(buff, msg);
//    }
//};
//
//TEST(connectionTest, ClientDispatcherTest){
//  auto msg = "hello world\n";
//  std::thread t([&](){
//      auto connMock = ServerConnector::connect(localhost, port);
//      connMock.send(msg, strlen(msg) + 1);
//      std::this_thread::sleep_for(std::chrono::seconds (1));
//  });
////  HandlerMock m{};
////  EXPECT_CALL(m, handle(_)).Times(1).WillRepeatedly([&](Connection c){
////    char buff[50];
////    c.receive(buff, 49);
////    ASSERT_STREQ(buff, msg);
////  });
//  DummyHandler handler;
//  ClientDispatcher dispatcher{handler};
//  dispatcher.dispatch();
//  t.join();
//}
