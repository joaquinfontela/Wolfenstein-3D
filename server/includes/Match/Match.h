#ifndef __MATCH_H__
#define __MATCH_H__

#include <map>

#include "../../../common/includes/Queue/NullPtrQueue.h"
#include "../../../common/includes/Thread/Thread.h"
#include "../Server/ClientCommunication.h"

class Match : public Thread {
 private:
  // TODO -> Aca iria lista de comandos que recibe el match
  // TODO -> Aca iria lista de notificaciones que deberia enviar el match

  int lobbyID;
  unsigned int playerCount;
  bool running;
  std::map<int, ClientCommunication*> players;

 public:
  Match(int lobbyID);
  bool hasID(int lobbyID);
  void run();
  bool hasEnded();

  void addPlayerToMatch(ClientCommunication* player);
};

#endif