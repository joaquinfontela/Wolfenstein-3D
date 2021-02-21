#include "../../includes/Match/Match.h"

#include "../../includes/Server/ClientCommunication.h"

#define MAP_YAML_FILE_NAME "/usr/local/share/Wolfenstein/YAML/map1.yaml"
#define CONFIG_YAML_FILE_NAME "/usr/local/share/Wolfenstein/YAML/config.yaml"

Match::Match(int lobbyID)
    : ID(lobbyID),
      playerCount(0),
      running(true),
      game(MAP_YAML_FILE_NAME, CONFIG_YAML_FILE_NAME) {
  cont = true;
}

Match::Match(int lobbyID, std::string mapFile, int mapID) : ID(lobbyID),
      playerCount(0),
      running(true),
      game(mapFile, CONFIG_YAML_FILE_NAME) {

  this->mapID = mapID;
  cont = true;
}
Match::Match() : game(MAP_YAML_FILE_NAME, CONFIG_YAML_FILE_NAME) {}

bool Match::hasID(int lobbyID) { return this->ID == lobbyID; }

void Match::forceShutdown() { this->running = false; }

ConnectionHandler* Match::addPlayerToMatch(ClientCommunication* player) {
  this->playerCount++;
  this->game.addPlayer(player->ID(), this->notis);

  this->players[player->ID()] = player;
  ConnectionHandler* playerHandler =
      new ConnectionHandler(player->getSock(), this->commands, player->ID());

  return playerHandler;
}

int Match::getMapID(){
  return this->mapID;
}

void Match::start() {
  engine = new Engine(commands, notis, cont, players, this->game);
  engine->start();
}

bool Match::hasEnded() { return !running; }

bool Match::isJoinable(){
  return (!this->game.hasStarted());
}

Match::~Match() {
  cont = false;
  engine->requestShutdown();
  engine->join();
  delete engine;
}
