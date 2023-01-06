cmake_minimum_required(VERSION 3.23)
project(updater)

set(CMAKE_CXX_STANDARD 20)

add_executable(updater main.cpp src/Connection.cpp src/Connection.hpp src/networking/ServerConnector.cpp src/networking/ServerConnector.hpp src/networking/ConnectionListener.cpp src/networking/ConnectionListener.hpp src/ClientHandler.cpp src/ClientHandler.hpp src/ClientDispatcher.cpp src/ClientDispatcher.hpp src/ServerCommunication.cpp src/ServerCommunication.hpp src/ProtocolUtil.cpp src/ProtocolUtil.hpp src/VersionDb.cpp src/VersionDb.hpp src/ClientCommunication.cpp src/ClientCommunication.hpp src/Version.cpp src/Version.hpp src/filesystem/FileUpdater.cpp src/filesystem/FileUpdater.hpp src/util/Logger.cpp src/util/Logger.hpp src/Changes.cpp src/Changes.hpp src/networking/TcpConnection.cpp src/networking/TcpConnection.hpp)

add_subdirectory(googleTest)

add_executable(Google_Tests_run src/Connection.cpp src/Connection.hpp src/networking/ServerConnector.cpp src/networking/ServerConnector.hpp tests/exampleTest.cpp src/networking/ConnectionListener.cpp src/networking/ConnectionListener.hpp src/ClientHandler.cpp src/ClientHandler.hpp src/ClientDispatcher.cpp src/ClientDispatcher.hpp tests/protocolTest.cpp src/ServerCommunication.cpp src/ServerCommunication.hpp src/ProtocolUtil.cpp src/ProtocolUtil.hpp src/VersionDb.cpp src/VersionDb.hpp src/ClientCommunication.cpp src/ClientCommunication.hpp src/Version.cpp src/Version.hpp src/filesystem/FileUpdater.cpp src/filesystem/FileUpdater.hpp src/util/Logger.cpp src/util/Logger.hpp src/Changes.cpp src/Changes.hpp tests/versionDbTest.cpp tests/ClientServerCommunicationTest.cpp tests/Mocks.hpp src/networking/TcpConnection.cpp src/networking/TcpConnection.hpp)
target_link_libraries(Google_Tests_run gtest gtest_main gmock gmock_main)

target_link_libraries(Google_Tests_run -lstdc++fs)
target_link_libraries(updater -lstdc++fs)
