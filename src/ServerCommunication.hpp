//
// Created by pavel on 11/28/22.
//

#ifndef UPDATER_SERVERCOMMUNICATION_HPP
#define UPDATER_SERVERCOMMUNICATION_HPP


#include "ClientHandler.hpp"
#include "VersionDb.hpp"

class ServerCommunication : public ClientHandler{
private:
    VersionDb &versionDb;
public:
    explicit ServerCommunication(VersionDb &versionDb);
    void handle(Connection &conn) override;
};


#endif //UPDATER_SERVERCOMMUNICATION_HPP
