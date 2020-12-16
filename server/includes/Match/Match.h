#ifndef __MATCH_H__
#define __MATCH_H__

#include <atomic>
#include <list>
#include <map>
#include <queue>

#include "../../../common/includes/Queue/NullPtrQueue.h"
#include "../Control/Command/Command.h"
#include "../Control/Notification/Notification.h"
#include "../Server/ClientCommunication.h"
#include "../Server/ConnectionHandler.h"
#include "Engine.h"

class Engine;
class ClientCommunication;

class Match {
 private:
  std::atomic<bool> cont;
  Engine* engine;
  NullPtrQueue<Command*> commands;

  int ID;
  unsigned int playerCount;
  bool running;
  std::map<int, ClientCommunication*> players;

 public:
  Match();
  ~Match();
  explicit Match(int lobbyID);
  void forceShutdown();
  bool hasID(int lobbyID);
  void start();
  bool hasEnded();

  ConnectionHandler* addPlayerToMatch(ClientCommunication* player);
};

#endif
