#include "../../../../includes/Model/Map/Tile/Tile.h"

Tile::Tile(int x, int y) {
  this->x = x;
  this->y = y;
  this->isWall = false;
}

void Tile::addDrop(int id) {
  ItemDrop i(id);
  drops.push_back(i);
}

std::vector<ItemDrop> Tile::getItemDrops() { return drops; }


bool Tile::allowMovement(double x, double y, Player* p){

  if(this->isWall)
    return false;

  std::vector<Player*>::iterator it = this->players.begin();

  for(; it != this->players.end(); ++it){

    if((*it) == p)
      continue;

    if((*it)->collidesWith(x, y))
      return false;
  }


  return true; // Faltaria chequear la interseccion con los jugadores.
}

bool Tile::checkWall(){
  return this->isWall;
}

Player* Tile::playerCollision(double x, double y){

  std::vector<Player*>::iterator it = this->players.begin();

  for(; it != this->players.end(); ++it){

    if((*it)->collidesWith(x, y))
      return (*it);
  }

  return nullptr;

}
void Tile::addPlayer(Player* p){
  this->players.push_back(p);

}
void Tile::setWall(){
  this->isWall = true;
}

void Tile::removePlayerFromTile(Player* p){

  std::vector<Player*>::iterator it = this->players.begin();

  for(; it != this->players.end(); ++it){

    if((*it) == p){
      this->players.erase(it);
      break;
    }
  }
}
