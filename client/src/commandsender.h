#ifndef COMMANDSENDER_H_
#define COMMANDSENDER_H_

#include "../../common/includes/Socket/SocketCommunication.h"
#include "../../common/includes/Socket/SocketException.h"
#include "../../common/includes/Thread/Thread.h"
#include "anglemanager.h"

#include <atomic>

class CommandSender : public Thread {
 public:
  CommandSender(SocketCommunication& s, std::atomic<bool> &alive);
  void update(uint32_t deltax, uint32_t deltay, double viewAngle, AngleManager& angles);
  void run();

 private:
  void update();
  SocketCommunication& socket;
  uint32_t x;
  uint32_t y;
  std::atomic<bool>& alive;
};

#endif  // COMMANDSENDER_H_
