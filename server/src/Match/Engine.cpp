#include "../../includes/Match/Engine.h"
#include "../../../common/includes/Socket/SocketException.h"

Engine::Engine(NullPtrQueue<Command*>& commandQ, std::atomic<bool>& c, std::map<int, ClientCommunication*>& play)
    : commandQueue(commandQ), cont(c), players(play) {}

void Engine::run() {
  std::thread t(&Engine::sendNotifications, this);
  while (cont) {
    Command* newCommand = commandQueue.pop();
    if (newCommand == nullptr) continue;
    newCommand->execute(notifications);
    delete newCommand;
  }
  std::cout << "[ENGINE] Joining sender thread" << std::endl;
  t.join();
}

void Engine::sendNotifications() {
  while (cont) {
    Notification* newNotification = notifications.pop();
    if (newNotification == nullptr) continue;
    std::cout << "[ENGINE] Sending Notification" << std::endl;
    for (auto& it : players) {
      ClientCommunication* c = it.second;
      try {
        newNotification->send(c->getSock());
      } catch (SocketException& e) {
      }
    }
  }
}
