#include "../../includes/Match/MatchList.h"

#include <iostream>
#include <map>

#include "../../includes/Match/Match.h"
#include "../../includes/Server/ClientCommunication.h"
#define MAP_YAML_FILE_NAME "/usr/local/share/Wolfenstein/YAML/Maps/map"

static bool fileExists(std::string& name){
  if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

MatchList::MatchList() {}

ConnectionHandler* MatchList::join(ClientCommunication* player, int lobbyID) {

  std::unique_lock<std::mutex> lock(this->lock);

  if (this->matches.find(lobbyID) != this->matches.end()) {
    return this->matches[lobbyID]->addPlayerToMatch(player);
  }

  return nullptr;
}

int MatchList::getMapID(int lobbyID){
  if (this->matches.find(lobbyID) != this->matches.end()) {
    return this->matches[lobbyID]->getMapID();
  }
  return -1;
}

std::vector<int> MatchList::getAvailableMatches(){
  std::vector<int> availableMatches;

  std::map<int, Match*>::iterator it = this->matches.begin();

  for(; it != this->matches.end(); ++it){

    if(it->second->isJoinable())
      availableMatches.push_back(it->first);
  }

  return availableMatches;
}

ConnectionHandler* MatchList::create(ClientCommunication* player, int mapID){
  std::unique_lock<std::mutex> lock(this->lock);

  std::string mapFile = MAP_YAML_FILE_NAME + std::to_string(mapID) + ".yaml";

  if(!fileExists(mapFile)){
    std::cout<<"[SERVER] Unable to create match with map: "<<mapFile<<std::endl;
    return nullptr;
  }


  int lobbyID = this->matchesCreated + 1;
  this->matchesCreated++;

  Match* newMatch = new Match(lobbyID, mapFile, mapID);
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
