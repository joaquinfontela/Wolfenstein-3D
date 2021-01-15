#ifndef COMMANDEXECUTER_H_
#define COMMANDEXECUTER_H_

#include <atomic>
#include <map>
#include <mutex>
#include <vector>

#include "player.h"
#include "audiomanager.h"
#include "../../common/includes/Socket/SocketCommunication.h"
#include "../../common/includes/Socket/SocketException.h"
#include "../../common/includes/Map/Map.h"
#include "../../common/includes/Thread/Thread.h"

typedef std::map<uint32_t,Player*>::iterator iterator_t;

class CommandExecuter : public Thread {
 public:
  CommandExecuter(SocketCommunication& s, std::atomic<bool>& alive, std::vector<Drawable*>& sprites,
                  std::map<uint32_t,Player*>& players,
                  std::mutex& lock, int selfId, AudioManager& audiomanager, Map& matrix) :
  socket(s) , alive(alive) , sprites(sprites), players(players) ,
  lock(lock) , selfId(selfId) , audiomanager(audiomanager) , matrix(matrix) {}
  ~CommandExecuter();
  void run();
 private:
  void removeSpriteWithId(int itemId);
  void playShootingSounds(int shooterId);
  SocketCommunication& socket;
  std::atomic<bool>& alive;
  std::vector<Drawable*>& sprites;
  std::map<uint32_t,Player*>& players;
  std::mutex& lock;
  int selfId;
  AudioManager& audiomanager;
  Map& matrix;
};

#endif  // COMMANDEXECUTER_H_
