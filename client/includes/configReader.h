#ifndef __CONFIG_READER_H__
#define __CONFIG_READER_H__
#include <yaml-cpp/yaml.h>


class ConfigReader{

private:
  std::string fileName;
  YAML::Node data;
  YAML::Node getData();

public:
    ConfigReader(std::string fileName);
    int getWidth();
    int getHeight();
    bool fullScreen();
};

#endif
