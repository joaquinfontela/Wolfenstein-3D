#ifndef TP_FINAL_ENGINE_H
#define TP_FINAL_ENGINE_H

#include <atomic>
#include <thread>
#include <mutex>

#include "../Model/Game/Game.h"
#include "../../../common/includes/Queue/WaitingQueue.h"
#include "../../../common/includes/Queue/WaitingQueue.h"
#include "../../../common/includes/Thread/Thread.h"
#include "../Control/Command/Command.h"
#include "../Control/Notification/Notification.h"
#include "../Server/ClientCommunication.h"

class ClientCommunication;

/**
  * @section DESCRIPTION
  * Class that simulates the passing of time and updates the status change to the clients.
*/
class Engine : public Thread {
 private:
  std::map<int, ClientCommunication*>& players;
  WaitingQueue<Command*>& commandQueue;
  WaitingQueue<Notification*>& notifications;
  std::atomic<bool>& cont;
  std::mutex gameLock;

  Game& thisGame;

 public:
  Engine(WaitingQueue<Command*>& commandQ, WaitingQueue<Notification*>& notiQ, std::atomic<bool>& c, std::map<int, ClientCommunication*>& play, Game& game);

  /**
    * <Forces shutdown of the engine>
  */
  void requestShutdown();

  /**
    * <Pops a command and executes it>
  */
  void executeCommands();

  /**
    * <Updates the game model>
    *
    * @param Time elapsed since last update.
  */
  void update(float timeElapsed);

  /**
    * <Runs the thread>
  */
  void run();

  /**
    * <Sends the notifications to the clients>
  */
  void sendNotifications();
};

#endif  // TP_FINAL_ENGINE_H
