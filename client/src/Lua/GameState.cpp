#include "GameState.h"
#include <iostream>
namespace Lua{

GameState::GameState(Map& matrix, Player* self) : matrix(matrix){ this->player = self;}

void GameState::addVisibleItem(Drawable* item){
  std::unique_lock<std::mutex> lock(this->lock);

  this->seenObjects.push_back(item);
}

void GameState::clearVisibleItems(){
  std::unique_lock<std::mutex> lock(this->lock);

  this->seenObjects.clear();
}

bool GameState::itemInSight(){
  std::unique_lock<std::mutex> lock(this->lock);

  return this->seenObjects.size() > 0;
}

bool GameState::facingWall(){
  std::unique_lock<std::mutex> lock(this->lock);

  double playerX = int(this->player->x);
  double playerY = int(this->player->y);
  double dirX = this->player->dirX;
  double dirY = this->player->dirY;

  int initialX = int(playerX);
  int initialY = int(playerY);

  while(initialX == int(playerX) && initialY == int(playerY)){
    playerX += dirX;
    playerY += dirY;
  }


  int* map = this->matrix.getMatrix();

  int mapX = int(playerX);
  int mapY = int(playerY);

  return (*(map + mapY + mapX * matrix.dimy) > 0);

}

bool GameState::playerInSight(){
  std::unique_lock<std::mutex> lock(this->lock);
  std::vector<Drawable*>::iterator it = this->seenObjects.begin();



  for(; it != this->seenObjects.end(); ++it){
    if((*it)->isPlayer()){
      std::cout<<"There is a player in sight"<<std::endl;
      return true;
    }
  }

  return false;
}

bool GameState::facingDoor(){
  return false;
}
}
