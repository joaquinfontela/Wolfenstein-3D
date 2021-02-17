#ifndef __STARTING_MATCH_NOTIF_H__
#define __STARTING_MATCH_NOTIF_H__
#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "Notification.h"


class StartingMatch : public Notification {
 public:
  StartingMatch() {}
  void send(SocketWrapper& socket);
};

#endif
