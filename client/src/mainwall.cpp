#include "../includes/client.h"
#include "../includes/clientprotocol.h"

#define INVALID_ARGS_ERR "Error, no hostname and/or port given."

int main(int argc, char** argv) {
  if (argc != 3) {
    LOG(INVALID_ARGS_ERR);
  }

  Client client;
  std::string mapFile = "../../common/src/YAML/map1.yaml";
  std::string host = argv[1];
  std::string port = argv[2];

  return client.run(host, port, 2, mapFile);
}
