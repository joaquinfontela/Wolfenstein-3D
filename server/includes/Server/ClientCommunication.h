#ifndef __CLIENT_COMMUNICATION_H__
#define __CLIENT_COMMUNICATION_H__

#include <list>
#include <queue>

#include "../../../common/includes/Queue/WaitingQueue.h"
#include "../../../common/includes/Socket/SocketWrapper.h"
#include "../../../common/includes/Thread/Thread.h"
#include "../../includes/Control/Command/Command.h"
#include "../../includes/Control/Notification/Notification.h"
#include "../../includes/Match/MatchList.h"
#include "ConnectionHandler.h"

class MatchList;

class ClientCommunication : public Thread {
 private:
  SocketCommunication socket;
  SocketWrapper wrapper;
  uint32_t playerID;
  MatchList& matchList;
  bool running;
  ConnectionHandler* handler;

  bool connectToLobby();

 public:
  ClientCommunication(SocketCommunication peer, uint32_t id,
                      MatchList& matches);

  unsigned int ID();

  void sendAvailableMatchData(std::vector<int>& matches);
  bool isAlive();
  SocketWrapper& getSock();

  void run();
};

#endif
