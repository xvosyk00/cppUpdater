//
// Created by pavel on 11/28/22.
//

#include <fstream>
#include <algorithm>
#include "VersionDb.hpp"

/* DB FILE FORMAT:
 * - list of versions and changes relative to previous currentVersion
 * - each entry in the list is composed of objects Version and Changes
 * - list must be sorted by currentVersion in ascending order
 * - last currentVersion is current currentVersion
 */

VersionDb::VersionDb(std::istream &dbFile) {
  parseDbFile(dbFile);
}

VersionDb::VersionDb(std::istream &&dbFile) {
  parseDbFile(dbFile);
}

void VersionDb::createNewVersion(const Version &newVersion, std::ostream &dbFileInAppendMode) {
//  currentVersion = newVersion;
//  changesCache[newVersion] = Changes{}; //todo
//  db << currentVersion;
//  db << changesCache.size();
//  std::vector<std::pair<Version, Changes>> loadedChanges;
//  for(auto& c : changesCache){
//    loadedChanges.emplace_back(c);
//  }
//  std::sort(loadedChanges.begin(),
//            loadedChanges.end(),
//            [](const auto& l, const auto& r){return l.first < r.first;}
//            );
  dbFileInAppendMode << newVersion << std::endl;
//  dbFileInAppendMode << changes; //todo compute changes and write them
}

const Changes &VersionDb::getChanges(const Version &oldVersion) {
  try{
    return changesCache.at(oldVersion);
  }catch (std::out_of_range &e){
    return allFilesChanged;
  }
}

const Version &VersionDb::getVersion() const {
  return currentVersion;
}

void VersionDb::parseDbFile(std::istream &db) {
  std::vector<std::pair<Version, Changes>> loadedChanges;
  // 1. load changes between versions from a file
  while (db.peek() != EOF) {
    Changes changes;
    Version changesVersion;
    db >> changesVersion;
    db >> changes;
    loadedChanges.emplace_back(changesVersion, changes);
  }
  if(loadedChanges.empty())
    throw std::runtime_error("DB file is not formatted correctly.");
  currentVersion = loadedChanges[loadedChanges.size() - 1].first;
  // 2. calculate changes between all versions and current one
  Changes changesToCurrentVersion = loadedChanges[loadedChanges.size() - 1].second;
  Version previousVersion = currentVersion;
  for(int i = loadedChanges.size() - 2; i >= 0; i--){
    auto& pair = loadedChanges[i];
    auto& changesVersion = pair.first;
    auto& changes = pair.second;
    if(changesVersion > previousVersion)
      throw std::runtime_error("Versions in file are not sorted properly.");
    changesCache[changesVersion] = changesToCurrentVersion; //save results to changesCache
    previousVersion = changesVersion;
    for(auto& c : changes){
      bool found = std::find_if(changesToCurrentVersion.begin(),
                                changesToCurrentVersion.end(),
                                [&c](const Change& change)
                                {return change.filename == c.filename;}
      ) != changesToCurrentVersion.end();
      if(!found){
        changesToCurrentVersion.push_back(c);
      }
    }
  }
  allFilesChanged = changesToCurrentVersion;
}
