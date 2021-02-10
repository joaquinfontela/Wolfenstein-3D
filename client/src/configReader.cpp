#include "../includes/configReader.h"

ConfigReader::ConfigReader(std::string fileName){
    this->fileName = fileName;
    this->data = this->getData();
}

YAML::Node ConfigReader::getData() {
  return YAML::LoadFile(this->fileName);
}

int ConfigReader::getHeight(){
    return data["HEIGHT"].as<int>();
}

int ConfigReader::getWidth(){
    return data["WIDTH"].as<int>();
}

bool ConfigReader::fullScreen() {
  return data["FULLSCREEN"].as<int>();
}
