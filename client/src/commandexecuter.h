#ifndef COMMANDEXECUTER_H_
#define COMMANDEXECUTER_H_

#include <map>

#include "../../common/includes/Socket/SocketCommunication.h"
#include "../../common/includes/Socket/SocketException.h"
#include "../../common/includes/Thread/Thread.h"
#include "player.h"

typedef std::map<uint32_t, Player*>::iterator iterator_t;

class CommandExecuter : public Thread {
 public:
  CommandExecuter(Player* self, uint32_t id, SocketCommunication& s);
  ~CommandExecuter();
  void run();

 private:
  std::map<uint32_t, Player*> players;
  SocketCommunication& socket;
};

#endif  // COMMANDEXECUTER_H_
