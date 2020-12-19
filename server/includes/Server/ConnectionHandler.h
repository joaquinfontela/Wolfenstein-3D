#ifndef __CONNECTION_HANDLER_H__
#define __CONNECTION_HANDLER_H__
#include "../../../common/includes/Queue/WaitingQueue.h"
#include "../../../common/includes/Socket/SocketCommunication.h"
#include "../Control/Command/Command.h"
#include "../Control/Notification/Notification.h"

class ConnectionHandler {
 private:
  SocketCommunication& socket;
  WaitingQueue<Command*>& commands;
  int ID;

 public:
  ConnectionHandler(SocketCommunication& sock, WaitingQueue<Command*>& com,
                    int playerID);
  void receiveCommands();
  void run();
};

#endif