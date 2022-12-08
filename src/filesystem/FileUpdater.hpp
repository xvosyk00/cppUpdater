//
// Created by pavel on 11/30/22.
//

#ifndef UPDATER_FILEUPDATER_HPP
#define UPDATER_FILEUPDATER_HPP


#include <string>

class FileUpdater {
public:
    virtual void deleteFile(const std::string &file) const;
    virtual void changeFile(const std::string &file, const char *content, int length) const;
};


#endif //UPDATER_FILEUPDATER_HPP
