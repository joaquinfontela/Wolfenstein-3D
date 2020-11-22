#include "../../includes/Server/Server.h"

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <string>

#include "../../../common/includes/Socket/SocketListener.h"
#include "../../includes/Server/ClientAccepter.h"

Server::Server(const std::string& port) { this->listener.bind(port); }

int Server::run() {
  std::cout << "[SERVER] Starting..." << std::endl;
  ClientAccepter accepter(this->listener);
  accepter.start();

  char c;

  while ((c = getchar()) != 'q') {
  }

  this->listener.close();
  accepter.join();

  std::cout << "[SERVER] Shutting down" << std::endl;
}