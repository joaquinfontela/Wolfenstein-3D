#include "client.h"
#include "clientprotocol.h"

#define INVALID_ARGS_ERR "Error, no hostname and/or port given."

int Log::playerId = -1;

int main(int argc, char** argv) {

  if (argc != 3) {
    LOG(INVALID_ARGS_ERR);
  }

  Client client;
  std::string mapFile = "../../common/src/YAML/map.yaml";
  std::string host = argv[1];
  std::string port = argv[2];

  return client.run(host, port, 2, mapFile);
}
