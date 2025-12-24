#include "ConfigManager.hpp"
#include "Logger.hpp"
#include <fstream>
#include <iostream>
#include <iomanip> 

#include "json.hpp"
using json = nlohmann::json;

ConfigManager* ConfigManager::instance = nullptr;
std::mutex ConfigManager::mutex_;

ConfigManager::ConfigManager() 
    : cameraId(0), frameWidth(640), frameHeight(480), logLevel("INFO"),
      modelProto("deploy.prototxt"), 
      modelWeights("res10_300x300_ssd_iter_140000.caffemodel"), 
      modelThreshold(0.5f) 
{}

ConfigManager& ConfigManager::getInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (instance == nullptr) {
        instance = new ConfigManager();
    }
    return *instance;
}

void ConfigManager::loadConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        Logger::getInstance().error("Could not open config file: " + filename);
        return;
    }

    try {
        json j;
        file >> j;

        if (j.contains("camera")) {
            cameraId = j["camera"].value("id", cameraId);
            frameWidth = j["camera"].value("width", frameWidth);
            frameHeight = j["camera"].value("height", frameHeight);
        }

        if (j.contains("logging")) {
            logLevel = j["logging"].value("level", logLevel);
        }

        if (j.contains("model")) {
            modelProto = j["model"].value("proto", modelProto);
            modelWeights = j["model"].value("weights", modelWeights);
            modelThreshold = j["model"].value("threshold", modelThreshold);
        }

        Logger::getInstance().info("Configuration loaded from " + filename);

    } catch (const json::parse_error& e) {
        Logger::getInstance().error("JSON parse error: " + std::string(e.what()));
    }
}

void ConfigManager::saveConfig(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        Logger::getInstance().error("Could not save config to: " + filename);
        return;
    }

    json j;

    j["camera"]["id"] = cameraId;
    j["camera"]["width"] = frameWidth;
    j["camera"]["height"] = frameHeight;
    
    j["logging"]["level"] = logLevel;
    
    j["model"]["proto"] = modelProto;
    j["model"]["weights"] = modelWeights;
    j["model"]["threshold"] = modelThreshold;

    file << j.dump(4); 
    
    file.close();
    Logger::getInstance().info("Configuration saved to " + filename);
}

int ConfigManager::getCameraId(int defaultVal) const { return cameraId; }
int ConfigManager::getFrameWidth(int defaultVal) const { return frameWidth; }
int ConfigManager::getFrameHeight(int defaultVal) const { return frameHeight; }
std::string ConfigManager::getLogLevel(const std::string& defaultVal) const { return logLevel; }
std::string ConfigManager::getModelProto(const std::string& defaultVal) const { return modelProto; }
std::string ConfigManager::getModelWeights(const std::string& defaultVal) const { return modelWeights; }
float ConfigManager::getModelThreshold(float defaultVal) const { return modelThreshold; }

void ConfigManager::setCameraId(int id) { cameraId = id; }
void ConfigManager::setFrameWidth(int width) { frameWidth = width; }
void ConfigManager::setFrameHeight(int height) { frameHeight = height; }
void ConfigManager::setLogLevel(const std::string& level) { logLevel = level; }
void ConfigManager::setModelProto(const std::string& proto) { modelProto = proto; }
void ConfigManager::setModelWeights(const std::string& weights) { modelWeights = weights; }
void ConfigManager::setModelThreshold(float threshold) { modelThreshold = threshold; }