#ifndef __MATCH_LIST_H__
#define __MATCH_LIST_H__

#include <map>

#include "../Server/ClientCommunication.h"
#include "../Server/ConnectionHandler.h"
#include "Match.h"

class ClientCommunication;
class Match;

typedef std::map<int, Match*>::iterator iterator_t;

class MatchList {
 private:
  std::map<int, Match*> matches;
  void forceShutdown();
  void matchCleanup();

 public:
  MatchList();
  // Intenta entrar a una partida, si la misma no existe, la crea.
  ConnectionHandler* joinOrCreate(ClientCommunication* player, int lobbyID);

  ~MatchList();
};

#endif
