#include "../includes/fileloader.h"

#include <fstream>

void FileLoader::loadFromFile(std::vector<std::string>& names, std::string filename) {
  std::ifstream reader;
  reader.open(filename, std::ifstream::in);
  while (reader.good()) {
    std::string line;
    std::getline(reader, line, '\n');
    if (line.empty()) continue;
    names.push_back(line);
  }
  reader.close();
}
