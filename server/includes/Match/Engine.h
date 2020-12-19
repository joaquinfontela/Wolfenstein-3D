#ifndef TP_FINAL_ENGINE_H
#define TP_FINAL_ENGINE_H

#include <atomic>
#include <thread>

#include "../Model/Game/Game.h"
#include "../../../common/includes/Queue/WaitingQueue.h"
#include "../../../common/includes/Queue/WaitingQueue.h"
#include "../../../common/includes/Thread/Thread.h"
#include "../Control/Command/Command.h"
#include "../Control/Notification/Notification.h"
#include "../Server/ClientCommunication.h"

class ClientCommunication;

class Engine : public Thread {
 private:
  std::map<int, ClientCommunication*>& players;
  WaitingQueue<Command*>& commandQueue;
  WaitingQueue<Notification*> notifications;
  std::atomic<bool>& cont;
  Game& thisGame;

 public:
  Engine(WaitingQueue<Command*>& commandQ, std::atomic<bool>& c, std::map<int, ClientCommunication*>& play, Game& game);
  void requestShutdown();
  void run();
  void sendNotifications();
};

#endif  // TP_FINAL_ENGINE_H
