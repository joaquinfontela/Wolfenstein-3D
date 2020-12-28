#include "../../includes/Socket/SocketWrapper.h"

#define PRECISION 100000

void SocketWrapper::send(double value) {
  uint32_t firstMessage = (uint32_t)value;
  uint32_t secondMessage = (value - (long int) value) * PRECISION;
  this->socket.send(firstMessage, sizeof(uint32_t));
  this->socket.send(secondMessage, sizeof(uint32_t));
}

double SocketWrapper::receive() {
  uint32_t firstReceived;
  uint32_t secondReceived;
  this->socket.receive(&firstMessage, sizeof(uint32_t));
  this->socket.receive(&secondMessage, sizeof(uint32_t));
  double ans = firstMessage + (((double)secondMessage) / PRECISION);
  return ((double)ans);
}
