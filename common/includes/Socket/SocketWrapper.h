#ifndef SOCKETWRAPPER_H_
#define SOCKETWRAPPER_H_

#include "SocketCommunication.h"

class SocketWrapper {
 private:
  SocketCommunication& socket;
 public:
  SocketWrapper(SocketCommunication& socket) : socket(socket) {}
  void send(double value);
  double receive();
};

#endif  // SOCKETWRAPPER_H_
