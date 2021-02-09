#include "server/includes/Server/Server.h"
#include <iostream>

int main(int argc, char** argv) {

  if(argc < 2){
    std::cout<<"Error. Server Execute Format: ./Server <PORT>"<<std::endl;
    return -1;
  }
  std::string port = argv[1];
  Server server(port);
  server.run();
}
