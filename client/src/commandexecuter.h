#ifndef COMMANDEXECUTER_H_
#define COMMANDEXECUTER_H_

#include <atomic>
#include <map>
#include <mutex>
#include <vector>

#include "player.h"
#include "audiomanager.h"
#include "ClientMapLoader.h"
#include "../../common/includes/Socket/SocketCommunication.h"
#include "../../common/includes/Socket/SocketException.h"
#include "../../common/includes/Map/Map.h"
#include "../../common/includes/Thread/Thread.h"

typedef std::map<uint32_t,Player*>::iterator iterator_t;

class CommandExecuter : public Thread {
 public:
  CommandExecuter(SocketCommunication& s, std::atomic<bool>& alive, std::vector<Drawable*>& sprites,
                  std::map<uint32_t,Player*>& players, std::mutex& lock, int selfId,
                  AudioManager& audiomanager, Map& matrix, ClientMapLoader& loader) :
  socket(s) , alive(alive) , sprites(sprites), players(players) , lock(lock) ,
  selfId(selfId) , audiomanager(audiomanager) , matrix(matrix) , loader(loader) {}
  ~CommandExecuter();
  void run();
 private:
  void renderMovingSprite(double x, double y, uint32_t itemId);
  void loadNewTexture(uint32_t x, uint32_t y, uint32_t yamlId, uint32_t uniqueId);
  void removeSpriteWithId(int itemId);
  void playShootingSounds(int shooterId);
  void playDoorOpeningSound(int x, int y);
  SocketCommunication& socket;
  std::atomic<bool>& alive;
  std::vector<Drawable*>& sprites;
  std::map<uint32_t,Player*>& players;
  std::mutex& lock;
  int selfId;
  AudioManager& audiomanager;
  Map& matrix;
  ClientMapLoader& loader;
};

#endif  // COMMANDEXECUTER_H_
