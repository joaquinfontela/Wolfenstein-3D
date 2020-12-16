#include "../../includes/Match/Match.h"

#include "../../includes/Server/ClientCommunication.h"

Match::Match(int lobbyID) : ID(lobbyID), playerCount(0), running(true) {
  cont = true;
  engine = new Engine(commands, cont, players);
}

Match::Match() {}

bool Match::hasID(int lobbyID) { return this->ID == lobbyID; }

void Match::forceShutdown() {
  this->running = false;
}

ConnectionHandler* Match::addPlayerToMatch(ClientCommunication* player) {
  this->playerCount++;

  this->players[player->ID()] = player;
  ConnectionHandler* playerHandler =
      new ConnectionHandler(player->getSock(), this->commands, player->ID());

  return playerHandler;
}

void Match::start() { engine->start(); }

bool Match::hasEnded() { return !running; }

Match::~Match() {
  cont = false;
  engine->join();
  delete engine;
}
