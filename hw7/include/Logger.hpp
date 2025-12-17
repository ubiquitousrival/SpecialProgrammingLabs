#pragma once
#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel {
    INFO = 0,
    WARN,
    ERROR
};

class Logger {
public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void setLevel(LogLevel level); // Новий метод
    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);

private:
    Logger();
    ~Logger();
    void log(LogLevel level, const std::string& message);
    std::string getCurrentTime();
    std::string getFileNameTimestamp();
    std::string levelToString(LogLevel level);

    std::ofstream logFile;
    std::mutex logMutex;
    LogLevel currentLevel; // Поточний фільтр
};