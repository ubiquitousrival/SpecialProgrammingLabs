#include "ConfigManager.hpp"
#include "Logger.hpp"
#include <fstream>
#include <iostream>

void ConfigManager::loadConfig(const std::string& filePath) {
    std::lock_guard<std::mutex> lock(configMutex);
    
    std::ifstream configFile(filePath);
    if (!configFile.is_open()) {
        Logger::getInstance().warn("Could not open settings.json. Using default values.");
        configData = json({}); 
        return;
    }

    try {
        configFile >> configData;
        Logger::getInstance().info("Configuration loaded successfully from " + filePath);
    } catch (const json::parse_error& e) {
        Logger::getInstance().error("JSON Parse Error: " + std::string(e.what()));
        configData = json({});
    }
}

int ConfigManager::getCameraId(int defaultVal) {
    if (configData.contains("camera") && configData["camera"].contains("id")) {
        return configData["camera"]["id"];
    }
    return defaultVal;
}

int ConfigManager::getFrameWidth(int defaultVal) {
    if (configData.contains("camera") && configData["camera"].contains("width")) {
        return configData["camera"]["width"];
    }
    return defaultVal;
}

int ConfigManager::getFrameHeight(int defaultVal) {
    if (configData.contains("camera") && configData["camera"].contains("height")) {
        return configData["camera"]["height"];
    }
    return defaultVal;
}

std::string ConfigManager::getModelProto(const std::string& defaultVal) {
    if (configData.contains("model") && configData["model"].contains("proto")) {
        return configData["model"]["proto"];
    }
    return defaultVal;
}

std::string ConfigManager::getModelWeights(const std::string& defaultVal) {
     if (configData.contains("model") && configData["model"].contains("weights")) {
        return configData["model"]["weights"];
    }
    return defaultVal;
}

float ConfigManager::getModelThreshold(float defaultVal) {
     if (configData.contains("model") && configData["model"].contains("threshold")) {
        return configData["model"]["threshold"];
    }
    return defaultVal;
}

std::string ConfigManager::getLogLevel(const std::string& defaultVal) {
     if (configData.contains("logging") && configData["logging"].contains("level")) {
        return configData["logging"]["level"];
    }
    return defaultVal;
}