#include "../../includes/Socket/SocketWrapper.h"
#include <iostream>

typedef union Floating {
  double d;
  uint32_t u32[2];
  char c[8];
} floating_t;

void SocketWrapper::send(double value) {
  floating_t sendable;
  sendable.d = value;
  this->socket.send(&sendable.u32[0], sizeof(uint32_t));
  this->socket.send(&sendable.u32[1], sizeof(uint32_t));
}

double SocketWrapper::receiveDouble() {
  floating_t sendable = {0};
  this->socket.receive(&sendable.u32[0], sizeof(uint32_t));
  this->socket.receive(&sendable.u32[1], sizeof(uint32_t));
  return sendable.d;
}

void SocketWrapper::send(PlayerData& value) {

  uint32_t lives = value.lives;
  uint32_t health = value.health;
  uint32_t weaponID = value.weaponID;
  uint32_t ammo = value.bullets;
  uint32_t score = value.score;
  uint32_t key =  value.hasKey ? 1 : 0;

  this->send(value.dirX);
  this->send(value.dirY);
  this->send(value.posX);
  this->send(value.posY);
  this->send(value.rotSpeed);
  this->socket.send(&lives, sizeof(uint32_t));
  this->socket.send(&health, sizeof(uint32_t));
  this->socket.send(&weaponID, sizeof(uint32_t));
  this->socket.send(&ammo, sizeof(uint32_t));
  this->socket.send(&score, sizeof(uint32_t));
  this->socket.send(&key, sizeof(uint32_t));
}

void SocketWrapper::receivePlayerData(PlayerData& value) {
  uint32_t lives = value.lives;
  uint32_t health = value.health;
  uint32_t weaponID = value.weaponID;
  uint32_t ammo = value.bullets;
  uint32_t score = value.score;
  uint32_t key = value.hasKey;

  this->socket.receive(&value.playerID, sizeof(value.playerID));
  value.dirX = this->receiveDouble();
  value.dirY = this->receiveDouble();
  value.posX = this->receiveDouble();
  value.posY = this->receiveDouble();
  value.rotSpeed = this->receiveDouble();
  this->socket.receive(&lives, sizeof(uint32_t));
  this->socket.receive(&health, sizeof(uint32_t));
  this->socket.receive(&weaponID, sizeof(uint32_t));
  this->socket.receive(&ammo, sizeof(uint32_t));
  this->socket.receive(&score, sizeof(uint32_t));
  this->socket.receive(&key, sizeof(uint32_t));


  value.lives = int(lives);
  value.health = int(health);
  value.weaponID = int(weaponID);
  value.bullets = int(ammo);
  value.score = int(score);
  value.hasKey = bool(key);
}
