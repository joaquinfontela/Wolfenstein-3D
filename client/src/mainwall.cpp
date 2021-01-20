#include "client.h"


#define INVALID_ARGS_ERR "Error, no hostname and/or port given."

int main(int argc, char** argv) {
  
  if (argc != 3) {
    std::cerr << INVALID_ARGS_ERR << std::endl;
  }

  Client client;
  std::string mapFile = "../../common/src/YAML/map.yaml";
  std::string host = argv[1];
  std::string port = argv[2];


  return client.run(host, port, 2, mapFile);
}
