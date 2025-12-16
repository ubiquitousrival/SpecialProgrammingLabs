#include "Logger.hpp"

Logger::Logger() {
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

void Logger::info(const std::string& message) {
    log("INFO", message);
}

void Logger::warn(const std::string& message) {
    log("WARN", message);
}

void Logger::error(const std::string& message) {
    log("ERROR", message);
}

void Logger::log(const std::string& level, const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);

    std::string timestamp = getCurrentTime();
    
    std::stringstream ss;
    ss << "[" << timestamp << "] [" << level << "] " << message;
    std::string finalMsg = ss.str();

    if (level == "ERROR") {
        std::cerr << "\033[31m" << finalMsg << "\033[0m" << std::endl;
    } else if (level == "WARN") {
        std::cout << "\033[33m" << finalMsg << "\033[0m" << std::endl;
    } else {
        std::cout << "\033[32m" << finalMsg << "\033[0m" << std::endl;
    }

    if (logFile.is_open()) {
        logFile << finalMsg << std::endl;
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
