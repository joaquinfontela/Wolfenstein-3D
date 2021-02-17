#ifndef SOCKETWRAPPER_H_
#define SOCKETWRAPPER_H_

#include "SocketCommunication.h"
#include "../PlayerData.h"

class SocketWrapper {
 private:
  SocketCommunication& socket;
 public:
  SocketWrapper(SocketCommunication& socket) : socket(socket) {}
  void send(double value);
  void send(uint32_t value);
  void receive(double* value);
  void receive(uint32_t* value);
  void send(PlayerData& value);
  void receivePlayerData(PlayerData& value);
  SocketCommunication& getSocket();
};

#endif  // SOCKETWRAPPER_H_
