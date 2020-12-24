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

void Game::playerShoot(int playerID){

    Player* attacker = this->players[playerID];

    Player* receiver = nullptr;
    int receiverHealth = 0;

    /* Comento por el momento hasta que tengamos la logica en el mapa.
    // En caso del Rocket Launcher, no deberia aplicar el daño instantaneamente si no crear un Rocket
    // y agregarlo a una lista de Actualizables dentro del juego.
    if((receiver = map.traceAttackFrom(attacker) != nullptr){
      receiverHealth = receiver->takeDamage(attacker->attack());

      if(receiverHealth == 0) // El jugador murio y debe respawnear
        this->map.handleRespawn(receiver);
    }
    */
}

int Game::moveDoor(int playerID){

    //return this->map.moveDoor(this->players[playerID]);
}

void Game::removePlayer(int playerID){

  std::map<int, Player*>::iterator it = this->players.find(playerID);

  if(it != this->players.end()){
      delete it->second;
      this->players.erase(it);
  }

}

void Game::start() {
  // Deberia controlar la logica de iniciar el juego -> mandar la notificacion a
  // los jugadores
}

void Game::end() {
  // Lo mismo pero para terminarlo.
}
