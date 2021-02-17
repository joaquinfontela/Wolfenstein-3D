#ifndef __PLAYER_PACKAGE_UPDATE_H__
#define __PLAYER_PACKAGE_UPDATE_H__

#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "../../../../common/includes/PlayerData.h"

#include "Notification.h"
class PlayerPackageUpdate : public Notification {
 private:
  int playerID;
  PlayerData data;

 public:
  PlayerPackageUpdate(int playerID, PlayerData data);

  void send(SocketWrapper& socket);
};

#endif
