#pragma once
#include <string>
#include <mutex>

class ConfigManager {
private:
    int cameraId;
    int frameWidth;
    int frameHeight;
    std::string logLevel;

    std::string modelProto;
    std::string modelWeights;
    float modelThreshold;
    
    ConfigManager();
    static ConfigManager* instance;
    static std::mutex mutex_;

public:
    ConfigManager(const ConfigManager&) = delete;
    void operator=(const ConfigManager&) = delete;

    static ConfigManager& getInstance();
    
    void loadConfig(const std::string& filename);
    void saveConfig(const std::string& filename); 

    int getCameraId(int defaultVal = 0) const;
    int getFrameWidth(int defaultVal = 640) const;
    int getFrameHeight(int defaultVal = 480) const;
    std::string getLogLevel(const std::string& defaultVal = "INFO") const;

    std::string getModelProto(const std::string& defaultVal = "deploy.prototxt") const;
    std::string getModelWeights(const std::string& defaultVal = "res10_300x300_ssd_iter_140000.caffemodel") const;
    float getModelThreshold(float defaultVal = 0.5f) const;

    void setCameraId(int id);
    void setFrameWidth(int width);
    void setFrameHeight(int height);
    void setLogLevel(const std::string& level);

    void setModelProto(const std::string& proto);
    void setModelWeights(const std::string& weights);
    void setModelThreshold(float threshold);
};