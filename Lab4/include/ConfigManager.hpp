#pragma once
#include <string>
#include <mutex>
#include "json.hpp"

using json = nlohmann::json;

class ConfigManager {
public:
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
    
    static ConfigManager& getInstance() {
        static ConfigManager instance;
        return instance;
    }

    void loadConfig(const std::string& filePath);

    int getCameraId(int defaultVal = 0);
    int getFrameWidth(int defaultVal = 640);
    int getFrameHeight(int defaultVal = 480);
    
    std::string getModelProto(const std::string& defaultVal = "deploy.prototxt");
    std::string getModelWeights(const std::string& defaultVal = "res10_300x300_ssd_iter_140000.caffemodel");
    float getModelThreshold(float defaultVal = 0.5f);
    
    std::string getLogLevel(const std::string& defaultVal = "INFO");

private:
    ConfigManager() = default;
    json configData;
    std::mutex configMutex;
};