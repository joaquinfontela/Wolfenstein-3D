#include "../../../includes/Model/Position/Position.h"

Position::Position(Player* player, Map& map) : player(player) {
  this->planeY = 0.66;
  this->planeX = 0;

  this->dirX = -1;
  this->dirY = 0;
  this->moveSpeed = 0;
  this->rotSpeed = 0;

  std::tie(this->x, this->y) = map.handleRespawn();
  map.addPlayer(this->x, this->y, this->player);
}

void Position::respawn(Map& map, WaitingQueue<Notification*>& notis){

  double x, y;

  std::tie(x, y) = map.handleRespawn();
  map.moveTo(this->x, this->y, x, y, this->player, notis);

  this->x = x;
  this->y = y;
}

void Position::fillData(PlayerData& data){
  data.posX = this->x;
  data.posY = this->y;
  data.dirX = this->dirX;
  data.dirY = this->dirY;
  data.rotSpeed = this->rotSpeed;
}

bool Position::update(Map& map, float timeElapsed, WaitingQueue<Notification*>& notis){

  if (moveSpeed == 0.0 && rotSpeed == 0.0) return false;


  double newX = this->x + this->dirX * (this->moveSpeed * (timeElapsed));
  double newY = this->y + this->dirY * (this->moveSpeed * (timeElapsed));

  double quarterStepX = (newX - x) / 4;
  double quarterStepY = (newY - y) / 4;

  int i = 0;
  while(i < 4){
    if(map.moveTo(x, y, x + quarterStepX, y + quarterStepY, this->player, notis)){
      x = x + quarterStepX;
      y = y + quarterStepY;
      i++;
    }else
      break;
  }

  double oldDirX = this->dirX;

  this->dirX = this->dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
  this->dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);

  double oldPlaneX = this->planeX;
  this->planeX = ((this->planeX) * cos(rotSpeed)) - (this->planeY * sin(rotSpeed));
  this->planeY = (oldPlaneX * sin(rotSpeed)) + (this->planeY * cos(rotSpeed));

  return true;
}

void Position::updateMoveSpeed(double moveSpeed){
  this->moveSpeed += moveSpeed;

  if(this->moveSpeed < -6.5)
    this->moveSpeed = -6.5;
  else if(this->moveSpeed > 6.5)
    this->moveSpeed = 6.5;
}

void Position::updateRotationSpeed(double rotSpeed){

  this->rotSpeed += rotSpeed;

  if(this->rotSpeed < -0.125)
    this->rotSpeed = -0.125;
  else if(this->rotSpeed > 0.125)
    this->rotSpeed = 0.125;
}

bool Position::collidesWith(double x, double y){
  return sqrt(pow(this->x - x, 2) + pow(this->y - y, 2)) <= 0.3;
}

double Position::getX(){
  return this->x;
}

double Position::getY(){
  return this->y;
}

double Position::getDirX(){
  return this->dirX;
}

double Position::getDirY(){
  return this->dirY;
}

double Position::getPlaneX(){
  return this->planeX;
}

double Position::getPlaneY(){
  return this->planeY;
}
