#ifndef LUAEXECUTER_H_
#define LUAEXECUTER_H_

#include <atomic>
#include <map>
#include <mutex>
#include <vector>

#include "../../../common/includes/Map/Map.h"
#include "../../../common/includes/Socket/SocketCommunication.h"
#include "../../../common/includes/Socket/SocketWrapper.h"
#include "../../common/includes/Socket/SocketWrapper.h"
#include "../../../common/includes/Socket/SocketException.h"
#include "../../../common/includes/Thread/Thread.h"
#include "../includes/ClientMapLoader.h"
#include "../includes/audiomanager.h"
#include "../includes/player.h"
#include "../includes/playermap.h"
#include "GameState.h"

namespace Lua {

class CommandExecuter : public Thread {
 public:
  CommandExecuter(SocketCommunication& s, std::atomic<bool>& alive,
                  std::vector<Drawable*>& sprites,
                  PlayerMap& players, std::mutex& lock,
                  int selfId, Map& matrix, ClientMapLoader& loader,
                  Lua::GameState& gameState)
      : socket(s),
        alive(alive),
        sprites(sprites),
        players(players),
        lock(lock),
        selfId(selfId),
        matrix(matrix),
        loader(loader),
        gameState(gameState) {}

  void run();

  ~CommandExecuter() {}

 private:
  void removeSpriteWithId(uint32_t itemId);
  void loadNewTexture(double x, double y, uint32_t yamlId, uint32_t uniqueId);
  void updateOrCreatePlayer(SocketWrapper& infogetter);
  void disconnectPlayer();
  void openDoor();
  void pickUpItem();
  void dropItem(SocketWrapper& infogetter);
  void switchElementPosition(SocketWrapper& infogetter);
  SocketWrapper socket;
  std::atomic<bool>& alive;
  Lua::GameState& gameState;
  std::vector<Drawable*>& sprites;
  PlayerMap& players;
  std::mutex& lock;
  int selfId;
  Map& matrix;
  ClientMapLoader& loader;
};

}  // namespace Lua

#endif  // LUAEXECUTER_H_
