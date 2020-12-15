#ifndef TP_FINAL_ENGINE_H
#define TP_FINAL_ENGINE_H

#include <atomic>
#include <thread>

#include "../../../common/includes/Queue/NullPtrQueue.h"
#include "../../../common/includes/Thread/Thread.h"
#include "../Control/Command/Command.h"
#include "../Control/Notification/Notification.h"
#include "../Server/ClientCommunication.h"

class ClientCommunication;

class Engine : public Thread {
 private:
  std::map<int, ClientCommunication*>& players;
  NullPtrQueue<Command*>& commandQueue;
  NullPtrQueue<Notification*> notifications;
  std::atomic<bool>& cont;

 public:
  Engine(NullPtrQueue<Command*>& commandQ, std::atomic<bool>& c, std::map<int, ClientCommunication*>& play);
  void run();
  void sendNotifications();
};

#endif  // TP_FINAL_ENGINE_H
