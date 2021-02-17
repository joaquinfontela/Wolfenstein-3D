#include "../../includes/Server/ClientAccepter.h"

#include "../../../common/includes/Socket/SocketException.h"
#include "../../../common/includes/Socket/SocketListener.h"
#include "../../includes/Match/MatchList.h"
#include "../../includes/Server/ClientCommunication.h"

ClientAccepter::ClientAccepter(SocketListener& listener, MatchList& matches)
    : socket(listener), matchList(matches) {}

void ClientAccepter::run() {
  uint32_t playerID = 1;

  while (1) {
    try {
      ClientCommunication* peer = new ClientCommunication(
          SocketCommunication(this->socket), playerID, matchList);
      playerID++;
      peer->start();

      std::cout << "[SERVER] Accepting new client..." << std::endl;

      this->peers.push_back(peer);
      //clientCleanup();
    } catch (SocketException& e) {
      while (!this->peers.empty()) {
        clientCleanup();
      }
      break;
    }
  }
}

void ClientAccepter::clientCleanup() {
  std::list<ClientCommunication*>::iterator it = this->peers.begin();

  while (it != this->peers.end()) {
    if (!(*it)->isAlive()) {
      (*it)->join();
      delete *it;
      it = this->peers.erase(it);
      std::cout << "[SERVER] Deleting client..." << std::endl;
    } else {
      ++it;
    }
  }
}
