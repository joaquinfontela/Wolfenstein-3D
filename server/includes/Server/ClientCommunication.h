#ifndef __CLIENT_COMMUNICATION_H__
#define __CLIENT_COMMUNICATION_H__

#include <list>
#include <queue>

#include "../../../common/includes/Queue/NullPtrQueue.h"
#include "../../../common/includes/Socket/SocketCommunication.h"
#include "../../../common/includes/Thread/Thread.h"
#include "../../includes/Control/Command/Command.h"
#include "../../includes/Control/Notification/Notification.h"
#include "../../includes/Match/MatchList.h"
#include "ConnectionHandler.h"

class MatchList;

class ClientCommunication : public Thread {
 private:
  SocketCommunication socket;
  uint32_t playerID;
  MatchList& matchList;
  bool running;
  ConnectionHandler* handler;

  bool connectToLobby();

 public:
  ClientCommunication(SocketCommunication peer, uint32_t id,
                      MatchList& matches);

  unsigned int ID();
  bool isAlive();
  SocketCommunication& getSock();

  void run();
};

#endif