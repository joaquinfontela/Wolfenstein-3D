#include "../../includes/Match/MatchList.h"

#include <iostream>
#include <map>

#include "../../includes/Match/Match.h"
#include "../../includes/Server/ClientCommunication.h"

MatchList::MatchList() {}

void MatchList::joinOrCreate(ClientCommunication* player, int lobbyID) {
  if (this->matches.find(lobbyID) != this->matches.end()) {
    this->matches[lobbyID].addPlayerToMatch(player);
    return;
  }

  Match newMatch(lobbyID);
  newMatch.addPlayerToMatch(player);

  newMatch.start();
  this->matches.insert({lobbyID, newMatch});
}

/*
void MatchList::matchCleanup() {
  std::map<int, Match*>::iterator it = this->matches.begin();

  while (it != this->matches.end()) {
    if (it->second->hasEnded()) {
      it->second->join();
      delete it->second;
      it = this->matches.erase(it);
      std::cout << "[SERVER] Deleting match..." << std::endl;
    } else {
      ++it;
    }
  }
}
*/

MatchList::~MatchList() {
  // while (!this->matches.empty()) {
  //   matchCleanup();
  // }
}