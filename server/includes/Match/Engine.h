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

  // Le pida a sus colas que cierren ordenadamente para poder finalizar la ejecucion.
  void requestShutdown();

  // Ejecuta en un loop los comandos que esten en la Queue
  void executeCommands();

  // Hace update del modelo del juego.
  void update(float timeElapsed);

  // Run para el thread.
  void run();

  // Envia las notificaciones que se encuentren en la Queue.
  void sendNotifications();
};

#endif  // TP_FINAL_ENGINE_H
