#ifndef __MATCH_LIST_H__
#define __MATCH_LIST_H__

#include <map>

#include "../Server/ClientCommunication.h"
#include "Match.h"

class ClientCommunication;
class Match;

class MatchList {
 private:
  std::map<int, Match> matches;

  // void matchCleanup();

 public:
  MatchList();
  // Intenta entrar a una partida, si la misma no existe, la crea.
  void joinOrCreate(ClientCommunication* player, int lobbyID);

  ~MatchList();
};

#endif