#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <ctime>
#include <iomanip>
#include <sstream>

class Logger {
public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);

private:
    Logger();
    ~Logger();

    void log(const std::string& level, const std::string& message);
    std::string getCurrentTime();
    std::string getFileNameTimestamp();

    std::ofstream logFile;
    std::mutex logMutex;
};
