#include "../../includes/Match/Match.h"

#include "../../includes/Server/ClientCommunication.h"

Match::Match(int lobbyID)
    : ID(lobbyID),
      playerCount(0),
      running(true),
      game("./common/src/YAML/map.yaml", "./common/src/YAML/config.yaml") {
  cont = true;
}

Match::Match()
    : game("./common/src/YAML/map.yaml", "./common/src/YAML/config.yaml") {}

bool Match::hasID(int lobbyID) { return this->ID == lobbyID; }

void Match::forceShutdown() { this->running = false; }

ConnectionHandler* Match::addPlayerToMatch(ClientCommunication* player) {
  this->playerCount++;
  this->game.addPlayer(player->ID());

  this->players[player->ID()] = player;
  ConnectionHandler* playerHandler =
      new ConnectionHandler(player->getSock(), this->commands, player->ID());

  return playerHandler;
}

void Match::start() {
  engine = new Engine(commands, cont, players, this->game);
  engine->start();
}

bool Match::hasEnded() { return !running; }

Match::~Match() {
  cont = false;
  engine->requestShutdown();
  engine->join();
  delete engine;
}
