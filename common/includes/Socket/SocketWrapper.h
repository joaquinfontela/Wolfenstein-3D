#ifndef SOCKETWRAPPER_H_
#define SOCKETWRAPPER_H_

#include "SocketCommunication.h"
#include "../../../server/includes/Model/Player/Player.h"

class SocketWrapper {
 private:
  SocketCommunication& socket;
 public:
  SocketWrapper(SocketCommunication& socket) : socket(socket) {}
  void send(double value);
  double receiveDouble();
  void send(PlayerData& value);
  void receivePlayerData(PlayerData& value);
};

#endif  // SOCKETWRAPPER_H_
