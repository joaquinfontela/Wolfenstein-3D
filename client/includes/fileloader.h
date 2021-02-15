#ifndef FILELOADER_H_
#define FILELOADER_H_

#include <vector>
#include <string>

class FileLoader {
 public:
 /**
  * @brief Reads a file containing all the soundtracks to use.
  *
  */
  void static loadFromFile(std::vector<std::string>& names, std::string filename);
};

#endif  // FILELOADER_H_
