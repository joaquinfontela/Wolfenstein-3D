#include <iostream>
#include <yaml-cpp/yaml.h>
//compile with flag -lyaml-cpp

int main() {
    YAML::Node data = YAML::LoadFile("example.yaml");

    std::cout << data["first-name"].as<std::string>() << std::endl;
    return 0;
}