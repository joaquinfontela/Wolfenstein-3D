#include "../../includes/Match/Engine.h"
#include "../../../common/includes/Socket/SocketException.h"
#include <iostream>

Engine::Engine(WaitingQueue<Command*>& commandQ, std::atomic<bool>& c, std::map<int, ClientCommunication*>& play, Game& game)
    : commandQueue(commandQ), cont(c), players(play), thisGame(game) {}

void Engine::run() {
  std::thread t(&Engine::sendNotifications, this);
  while (cont) {
    Command* newCommand = nullptr;
    newCommand = commandQueue.pop();
    if (newCommand == nullptr) continue;
    newCommand->execute(notifications, this->thisGame);
    delete newCommand;
  }
  std::cout << "[ENGINE] Joining sender thread" << std::endl;
  t.join();
}

void Engine::requestShutdown(){
  commandQueue.requestShutdown();
  notifications.requestShutdown();
}

void Engine::sendNotifications() {
  while (cont) {
    Notification* newNotification = nullptr;
    newNotification = notifications.pop();
    if (newNotification == nullptr) continue;
    std::cout << "[ENGINE] Sending Notification" << std::endl;
    for (auto& it : players) {
      ClientCommunication* c = it.second;
      try {
        newNotification->send(c->getSock());
        delete newNotification;
      } catch (SocketException& e) {
      }
    }
  }
}
