#include "../../includes/Match/MatchList.h"

#include <iostream>
#include <map>

#include "../../includes/Match/Match.h"
#include "../../includes/Server/ClientCommunication.h"

MatchList::MatchList() {}

ConnectionHandler* MatchList::join(ClientCommunication* player,
                                           int lobbyID) {

  std::unique_lock<std::mutex> lock(this->lock);
  if (this->matches.find(lobbyID) != this->matches.end()) {
    return this->matches[lobbyID]->addPlayerToMatch(player);
  }

  // Deberia en realidad devolver algo del estilo CONNECTION_REFUSED por el socket.
  Match* newMatch = new Match(lobbyID);
  ConnectionHandler* playerHandler = newMatch->addPlayerToMatch(player);

  newMatch->start();
  this->matches[lobbyID] = newMatch;
  return playerHandler;
}

ConnectionHandler* MatchList::create(ClientCommunication* player, int lobbyID){
  std::unique_lock<std::mutex> lock(this->lock);
  if (this->matches.find(lobbyID) != this->matches.end()) {
    // Devolver CONNECTION_REFUSED como codigo de error.
  }

  Match* newMatch = new Match(lobbyID);
  ConnectionHandler* playerHandler = newMatch->addPlayerToMatch(player);

  newMatch->start();
  this->matches[lobbyID] = newMatch;
  return playerHandler;
}

void MatchList::matchCleanup() {
  std::map<int, Match*>::iterator it = this->matches.begin();

  while (it != this->matches.end()) {
    if (it->second->hasEnded()) {
      delete it->second;
      it = this->matches.erase(it);
      std::cout << "[SERVER] Deleting match..." << std::endl;
    } else {
      ++it;
    }
  }
}

void MatchList::forceShutdown() {
  for (iterator_t it = this->matches.begin(); it != this->matches.end(); ++it){
    it->second->forceShutdown();
  }
}

MatchList::~MatchList() {
  this->forceShutdown();
  while (!this->matches.empty()) {
    matchCleanup();
  }
}
