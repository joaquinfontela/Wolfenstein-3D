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
  ScoreBoard* shotsScoreboard;
 public:
  EndMatchNotif(ScoreBoard* scoreboard, ScoreBoard* kills, ScoreBoard* shotsFired) : scoreboard(scoreboard), killScoreboard(kills), shotsScoreboard(shotsFired) {}
  ~EndMatchNotif();
  void send(SocketWrapper& socket);
};

#endif
