#include "Logger.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

Logger::Logger() : currentLevel(LogLevel::INFO) {
    std::string filename = "log_" + getFileNameTimestamp() + ".txt";
    logFile.open(filename, std::ios::out);
    if (logFile.is_open()) {
        logFile << "Log file created: " << filename << std::endl;
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::setLevel(LogLevel level) {
    currentLevel = level;
}

void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warn(const std::string& message) {
    log(LogLevel::WARN, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

void Logger::log(LogLevel level, const std::string& message) {
    if (level < currentLevel) {
        return;
    }

    std::lock_guard<std::mutex> lock(logMutex);
    std::string timestamp = getCurrentTime();
    std::string levelStr = levelToString(level);
    
    std::stringstream ss;
    ss << "[" << timestamp << "] [" << levelStr << "] " << message;
    std::string finalMsg = ss.str();

    if (level == LogLevel::ERROR) {
        std::cerr << "\033[31m" << finalMsg << "\033[0m" << std::endl;
    } else if (level == LogLevel::WARN) {
        std::cout << "\033[33m" << finalMsg << "\033[0m" << std::endl;
    } else {
        std::cout << "\033[32m" << finalMsg << "\033[0m" << std::endl;
    }

    if (logFile.is_open()) {
        logFile << finalMsg << std::endl;
    }
}

std::string Logger::levelToString(LogLevel level) {
    switch(level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARN: return "WARN";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

std::string Logger::getCurrentTime() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string Logger::getFileNameTimestamp() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
    return oss.str();
}