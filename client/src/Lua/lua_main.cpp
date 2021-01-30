#include "LuaClient.h"
#include <string>

#define INVALID_ARGS_ERR "Error, no hostname and/or port given."

int main(int argc, char* argv[]){

  if (argc != 4) {
    LOG(INVALID_ARGS_ERR);
  }

  Lua::Client client;
  std::string mapFile = "../../common/src/YAML/map.yaml";
  std::string host = argv[1];
  std::string port = argv[2];
  std::string scriptName = argv[3];

  return client.run(host, port, 2, mapFile, scriptName);
}
