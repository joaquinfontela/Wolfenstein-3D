#include "../../../includes/Model/Game/Game.h"

#include <string>

#include "../../../includes/Model/Player/Player.h"

Game::Game(std::string& mapFile, std::string& configFile) {}

void Game::addPlayer(int playerID) {
  unsigned int health = 100;  // Deberian obtenerse del file de config.
  unsigned int lifes = 2;

  Player newPlayer(health, lifes);
  this->players[playerID] = newPlayer;
}

void Game::start() {
  // Deberia controlar la logica de iniciar el juego -> mandar la notificacion a
  // los jugadores
}

void Game::end() {
  // Lo mismo pero para terminarlo.
}