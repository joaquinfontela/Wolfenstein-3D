#include "LuaClient.h"
#include <cstdlib>
#include <string>

#define INVALID_ARGS_ERR "Error, no hostname and/or port given."

int main(int argc, char* argv[]){

  if (argc != 5) {
    LOG(INVALID_ARGS_ERR);
  }

  Lua::Client client;

  std::string host = argv[1];
  std::string port = argv[2];
  std::string scriptName = argv[3];
  int matchID = atoi(argv[4]);

  return client.run(host, port, matchID, scriptName);
}
