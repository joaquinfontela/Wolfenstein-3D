#ifndef __END_MATCH_NOTIF_H__
#define __END_MATCH_NOTIF_H__
#include "ScoreBoard.h"
#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "Notification.h"

#include <vector>

class EndMatchNotif : public Notification {
 private:
  ScoreBoard* scoreboard;
  ScoreBoard* killScoreboard;
 public:
  EndMatchNotif(ScoreBoard* scoreboard, ScoreBoard* kills) : scoreboard(scoreboard), killScoreboard(kills) {}
  ~EndMatchNotif();
  void send(SocketCommunication& socket);
};

#endif
