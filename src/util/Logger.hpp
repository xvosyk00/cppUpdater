//
// Created by pavel on 12/1/22.
//

#ifndef UPDATER_LOGGER_HPP
#define UPDATER_LOGGER_HPP

#include <fstream>
#include <string>

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)
#define logDebug(msg) termMiner::backend::Logger::debug(__FILENAME__, __func__, msg)

class Logger {
public:
    Logger(std::string logFile);
    static void info(const std::string &str);
    static void debug(const std::string &str);
    static void debug(const std::string &source, const std::string &function, const std::string &str);
    static void error(const std::string &str);
    ~Logger();

private:
    std::ofstream log;
};

#endif //UPDATER_LOGGER_HPP
