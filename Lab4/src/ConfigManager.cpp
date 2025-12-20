#include "ConfigManager.hpp"
#include "Logger.hpp"
#include <fstream>
#include <iostream>

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
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("\"id\"") != std::string::npos) {
            try { cameraId = std::stoi(line.substr(line.find(":") + 1)); } catch(...) {}
        }
        else if (line.find("\"width\"") != std::string::npos) {
            try { frameWidth = std::stoi(line.substr(line.find(":") + 1)); } catch(...) {}
        }
        else if (line.find("\"level\"") != std::string::npos) {
            size_t start = line.find(": \"");
            size_t end = line.find("\"", start + 3);
            if (start != std::string::npos && end != std::string::npos) {
                logLevel = line.substr(start + 3, end - start - 3);
            }
        }
        else if (line.find("\"proto\"") != std::string::npos) {
            size_t start = line.find(": \"");
            size_t end = line.find("\"", start + 3);
            if (start != std::string::npos && end != std::string::npos) {
                modelProto = line.substr(start + 3, end - start - 3);
            }
        }
        else if (line.find("\"weights\"") != std::string::npos) {
            size_t start = line.find(": \"");
            size_t end = line.find("\"", start + 3);
            if (start != std::string::npos && end != std::string::npos) {
                modelWeights = line.substr(start + 3, end - start - 3);
            }
        }
        else if (line.find("\"threshold\"") != std::string::npos) {
             try { modelThreshold = std::stof(line.substr(line.find(":") + 1)); } catch(...) {}
        }
    }
    file.close();
    Logger::getInstance().info("Configuration loaded from " + filename);
}

void ConfigManager::saveConfig(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        Logger::getInstance().error("Could not save config to: " + filename);
        return;
    }

    file << "{\n";
    file << "    \"camera\": {\n";
    file << "        \"id\": " << cameraId << ",\n";
    file << "        \"width\": " << frameWidth << ",\n";
    file << "        \"height\": " << frameHeight << "\n";
    file << "    },\n";
    file << "    \"logging\": {\n";
    file << "        \"level\": \"" << logLevel << "\"\n";
    file << "    },\n";
    file << "    \"model\": {\n";
    file << "        \"proto\": \"" << modelProto << "\",\n";
    file << "        \"weights\": \"" << modelWeights << "\",\n";
    file << "        \"threshold\": " << modelThreshold << "\n";
    file << "    }\n";
    file << "}";
    
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