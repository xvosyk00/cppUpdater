//
// Created by pavel on 11/28/22.
//

#ifndef UPDATER_VERSIONDB_HPP
#define UPDATER_VERSIONDB_HPP


#include "Version.hpp"
#include <unordered_map>
#include "Changes.hpp"

static const char *const dbFilename = "updater.db";

class VersionDb {
private:
    Version currentVersion{};
    std::unordered_map<Version, Changes> changesCache;
    Changes allFilesChanged;
    void parseDbFile(std::istream &dbFile);
public:
    explicit VersionDb(std::istream &dbFile);
    explicit VersionDb(std::istream &&dbFile);
    [[nodiscard]] const Version &getVersion() const;
    const Changes &getChanges(const Version &oldVersion);
    void createNewVersion(const Version &newVersion, std::ostream &dbFileInAppendMode);
};


#endif //UPDATER_VERSIONDB_HPP
