#include "../../../includes/Model/Game/Game.h"

#include <string>

#include "../../../includes/Model/Player/Player.h"

Game::Game(std::string mapFile, std::string configFile) : map(mapFile) {}

void Game::addPlayer(int playerID) {
  unsigned int health = 100;  // Deberian obtenerse del file de config.
  unsigned int lifes = 2;

  Player* newPlayer = new Player(health, lifes);
  this->players[playerID] = newPlayer;
}

void Game::removePlayer(int playerID){
  delete this->players[playerID];
  this->players.erase(playerID);
}

void Game::updatePlayerMoveSpeed(int playerID, double moveSpeed){
  this->players[playerID]->updateMoveSpeed(moveSpeed);
}

void Game::updatePlayerRotationSpeed(int playerID, double rotSpeed){
  this->players[playerID]->updateRotationSpeed(rotSpeed);
}
void Game::start() {
  // Deberia controlar la logica de iniciar el juego -> mandar la notificacion a
  // los jugadores
}

void Game::end() {
  // Lo mismo pero para terminarlo.
}
