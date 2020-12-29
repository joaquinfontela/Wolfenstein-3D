#include "../../includes/Socket/SocketWrapper.h"
#include <iostream>

#define PRECISION 100000

void SocketWrapper::send(double value) {
  uint32_t signo = 0;
  if(value < 0){
    uint32_t signo = 1;
    value = abs(value);
  }
  this->socket.send(&signo, sizeof(signo));

  uint32_t firstMessage = (uint32_t)value;
  uint32_t secondMessage = (value - (long int) value) * PRECISION;
  this->socket.send(&firstMessage, sizeof(uint32_t));
  this->socket.send(&secondMessage, sizeof(uint32_t));
}

double SocketWrapper::receiveDouble() {
  uint32_t signo;
  uint32_t firstReceived;
  uint32_t secondReceived;

  this->socket.receive(&signo, sizeof(uint32_t));

  this->socket.receive(&firstReceived, sizeof(uint32_t));
  this->socket.receive(&secondReceived, sizeof(uint32_t));
  double ans = firstReceived + (((double)secondReceived) / PRECISION);

  if(signo == 1)
    ans *= -1;

  return ((double)ans);
}

void SocketWrapper::send(PlayerData& value) {

  this->socket.sendDouble(&value.dirX, sizeof(double));
  this->socket.sendDouble(&value.dirY, sizeof(double));
  this->socket.sendDouble(&value.posX, sizeof(double));
  this->socket.sendDouble(&value.posY, sizeof(double));
  this->socket.sendDouble(&value.rotSpeed, sizeof(double));

  //this->send((const double)value.dirX);
  //this->send((const double)value.dirY);
  //this->send((const double)value.posX);
  //this->send((const double)value.posY);
  //this->send((const double)value.rotSpeed);
  //this->socket.send(value.weaponID, sizeof(uint32_t));
  //this->socket.send(value.lives, sizeof(uint32_t));
  //this->socket.send(value.health, sizeof(uint32_t));
}

void SocketWrapper::receivePlayerData(PlayerData& value) {

  this->socket.receive(&value.playerID, sizeof(value.playerID));
  this->socket.receiveDouble(&value.dirX, sizeof(double));
  this->socket.receiveDouble(&value.dirY, sizeof(double));
  this->socket.receiveDouble(&value.posX, sizeof(double));
  this->socket.receiveDouble(&value.posY, sizeof(double));
  this->socket.receiveDouble(&value.rotSpeed, sizeof(double));
//  this->socket.receive(&value.playerID, sizeof(value.playerID));
//  value.dirX = this->receiveDouble();
//  std::cout<<"DirX: "<<value.dirX<<std::endl;
//  value.dirY = this->receiveDouble();
//  std::cout<<"DirY: "<<value.dirY<<std::endl;
//  value.posX = this->receiveDouble();
//  value.rotSpeed = this->receiveDouble();
  //this->socket.receive(&value.weaponID, sizeof(uint32_t));
  //this->socket.receive(&value.lives, sizeof(uint32_t));
  //this->socket.senreceived(&value.health, sizeof(uint32_t));
}
