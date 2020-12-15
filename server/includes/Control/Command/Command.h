#ifndef __COMMAND_H__
#define __COMMAND_H__
#include <list>

#include "../../../../common/includes/Queue/NullPtrQueue.h"
#include "../Notification/Notification.h"

class Command {
 public:
  virtual void execute(NullPtrQueue<Notification*>& notifications) = 0;
  virtual ~Command(){};
};

#endif