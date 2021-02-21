#include "../../includes/Socket/SocketWrapper.h"
#include <iostream>
#include <arpa/inet.h>

#define BYTESIZE sizeof(char)

typedef union Floating {
  double d;
  uint32_t u[2];
} floating_t;

typedef union b32 {
  uint32_t u32;
  char c[4];
} b32_t;

SocketCommunication& SocketWrapper::getSocket() {
  return this->socket;
}

void SocketWrapper::send(double value) {
  floating_t sendable;
  sendable.d = value;
  this->send(sendable.u[0]);
  this->send(sendable.u[1]);
}

void SocketWrapper::receive(double* value) {
  floating_t receivable = {0};
  this->receive(&receivable.u[0]);
  this->receive(&receivable.u[1]);
  *value = receivable.d;
}

void SocketWrapper::send(uint32_t value) {
  b32_t sendable;
  sendable.u32 = htonl(value);
  this->socket.send(&sendable.c[0], BYTESIZE);
  this->socket.send(&sendable.c[1], BYTESIZE);
  this->socket.send(&sendable.c[2], BYTESIZE);
  this->socket.send(&sendable.c[3], BYTESIZE);
}

void SocketWrapper::receive(uint32_t* value) {
  b32_t receivable = {0};
  this->socket.receive(&receivable.c[0], BYTESIZE);
  this->socket.receive(&receivable.c[1], BYTESIZE);
  this->socket.receive(&receivable.c[2], BYTESIZE);
  this->socket.receive(&receivable.c[3], BYTESIZE);
  *value = ntohl(receivable.u32);
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
  this->send(lives);
  this->send(health);
  this->send(weaponID);
  this->send(ammo);
  this->send(score);
  this->send(key);
}

void SocketWrapper::receivePlayerData(PlayerData& value) {
  uint32_t lives = value.lives;
  uint32_t health = value.health;
  uint32_t weaponID = value.weaponID;
  uint32_t ammo = value.bullets;
  uint32_t score = value.score;
  uint32_t key = value.hasKey;

  this->receive(&value.playerID);
  this->receive(&value.dirX);
  this->receive(&value.dirY);
  this->receive(&value.posX);
  this->receive(&value.posY);
  this->receive(&value.rotSpeed);
  this->receive(&lives);
  this->receive(&health);
  this->receive(&weaponID);
  this->receive(&ammo);
  this->receive(&score);
  this->receive(&key);

  value.lives = int(lives);
  value.health = int(health);
  value.weaponID = int(weaponID);
  value.bullets = int(ammo);
  value.score = int(score);
  value.hasKey = bool(key);
}
