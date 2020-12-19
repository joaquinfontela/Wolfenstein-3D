#ifndef __COMMAND_H__
#define __COMMAND_H__


#include "../../Model/Game/Game.h"
#include "../../../../common/includes/Queue/WaitingQueue.h"
#include "../Notification/Notification.h"

class ClientCommunication;

class Command {
 public:
  virtual void execute(WaitingQueue<Notification*>& notifications, Game& game) = 0;
  virtual ~Command(){};
};

#endif
