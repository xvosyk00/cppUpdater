//
// Created by pavel on 11/30/22.
//

#include "FileUpdater.hpp"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void FileUpdater::deleteFile(const std::string &file) const {
  fs::remove(file);
}

void FileUpdater::changeFile(const std::string &file, const char *content, int length) const {
  std::string directory = file.substr(0, file.find_last_of("\\/"));
  fs::create_directories(directory);
  std::ofstream fileHandle(file, std::ios::binary | std::ios::trunc);
  fileHandle.write(content, length);
  fileHandle.close();
}
