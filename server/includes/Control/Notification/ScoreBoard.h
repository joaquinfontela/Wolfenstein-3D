#ifndef __SCORE_BOARD_H__
#define __SCORE_BOARD_H__
#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "Notification.h"

#include <vector>

class ScoreBoard : public Notification {
 private:
  int numberOfPlayers;
  std::vector<uint32_t> players;
  std::vector<uint32_t> scores;
 public:
  ScoreBoard(int numberOfPlayers, std::vector<uint32_t> players, std::vector<uint32_t> scores) :
             numberOfPlayers(numberOfPlayers), players(players), scores(scores) {}
  void send(SocketWrapper& socket);
};

#endif
