#ifndef __MATCH_H__
#define __MATCH_H__

#include <map>

#include "../Server/ClientCommunication.h"

class ClientCommunication;

class Match {
 private:
  // TODO -> Aca iria lista de comandos que recibe el match
  // TODO -> Aca iria lista de notificaciones que deberia enviar el match

  int ID;
  unsigned int playerCount;
  bool running;
  std::map<int, ClientCommunication*> players;

 public:
  explicit Match(int lobbyID);
  bool hasID(int lobbyID);
  void start();
  bool hasEnded();

  void addPlayerToMatch(ClientCommunication* player);
};

#endif