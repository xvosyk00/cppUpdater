//
// Created by pavel on 11/29/22.
//

#ifndef UPDATER_CLIENTCOMMUNICATION_HPP
#define UPDATER_CLIENTCOMMUNICATION_HPP

#include <string>
#include <memory>
#include "Version.hpp"
#include "Connection.hpp"
#include "ProtocolUtil.hpp"
#include "filesystem/FileUpdater.hpp"
#include "networking/ServerConnector.hpp"

struct CheckResult{
    bool success;
    bool serverHasNewerVersion;
};

struct UpdateResult{
    bool success;
    bool updated;
};

class ClientCommunication {
    Version version;
    std::string server;
    FileUpdater &fileUpdater;
    ServerConnector &serverConnector;
    int port = ProtocolUtil::port;
    void update(Connection &connection) const;
public:
    ClientCommunication(Version version, std::string serverHostname, FileUpdater &fileUpdater, ServerConnector &serverConnector);
    /**
     * Tries to connect to a server and updates to the newer version if available.
     */
    UpdateResult checkAndUpdate() const;
    /**
     * Tries to connect to a server and find out if newer version is available.
     */
    CheckResult checkVersion() const;
};


#endif //UPDATER_CLIENTCOMMUNICATION_HPP
