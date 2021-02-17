#ifndef __SHOTS_FIRED__
#define __SHOTS_FIRED__

#include "Notification.h"


class ShotsFired : public Notification{

private:
  int playerID;

public:
  ShotsFired(int playerID);
  void send(SocketWrapper& socket);

};

#endif
