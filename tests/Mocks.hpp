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

#endif //UPDATER_MOCKS_HPP
