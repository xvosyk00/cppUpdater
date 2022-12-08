//
// Created by pavel on 12/1/22.
//

#include "Logger.hpp"
#include <iostream>
#include <ctime>
#include <filesystem>

Logger *logger;
const char *errorText = "\033[1;31m";
const char *debugText = "\033[1;90m";
const char *resetText = "\033[0m";

void Logger::info(const std::string &str) {
  logger->log << "info: " << str << "\n";
  logger->log.flush();
}

void Logger::debug(const std::string &str) {
  logger->log << "debug: " << str << "\n";
  logger->log.flush();
}

void Logger::debug(const std::string &source, const std::string &function, const std::string &str) {
  logger->log << debugText << "debug <" << source << "::" << function << ">: " << resetText << str << "\n";
  logger->log.flush();
}

void Logger::error(const std::string &str) {
  logger->log << errorText << "error: " << str << resetText << "\n";
  logger->log.flush();
}

Logger::Logger(std::string logFile) {
  if (logger)
    throw std::runtime_error("Logger instance already exists.");
  logger = this;
  bool dirCreated = false;
  std::string directory = logFile.substr(0, logFile.find_last_of("\\/"));
  if(!std::filesystem::exists(directory)){
    std::filesystem::create_directory(directory);
    dirCreated = true;
  }
  log.open(logFile, std::ios::out | std::ios::app);
  if(!log.is_open())
    throw std::runtime_error("Failed to open log " + logFile);
  auto now = time(0);
  log << "\nLog file opened at " << std::ctime(&now);
  if(dirCreated)
    info("Log directory was not found and was created.");
}

Logger::~Logger() {
  log << "closing log file\n";
  log.close();
}
