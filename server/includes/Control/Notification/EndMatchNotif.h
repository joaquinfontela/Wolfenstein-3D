#ifndef __END_MATCH_NOTIF_H__
#define __END_MATCH_NOTIF_H__
#include "ScoreBoard.h"
#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "Notification.h"

#include <vector>

class EndMatchNotif : public Notification {
 private:
  ScoreBoard* scoreboard;
 public:
  EndMatchNotif(ScoreBoard* scoreboard) : scoreboard(scoreboard) {}
  ~EndMatchNotif();
  void send(SocketCommunication& socket);
};

#endif
