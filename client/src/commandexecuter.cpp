#include "commandexecuter.h"

#include <SDL2/SDL.h>

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <thread>

#include "../../common/includes/protocol.h"
#include "player.h"

#define IMG_PATH "../media/"
#define GENERIC_ERROR \
  "Error occured while reading info from the server or while drawing."
#define OUT_OF_BOUNDS std::numeric_limits<int>::min()

CommandExecuter::CommandExecuter(Player* self, uint32_t id, SocketCommunication& s) : socket(s) {
  players[id] = self;
}

CommandExecuter::~CommandExecuter() {
  for (auto& r : players) {
    delete r.second;
  }
}

void CommandExecuter::run() {
  while (true) {
    try {
      uint32_t opcode;
      uint32_t id;
      uint32_t x;
      uint32_t y;
      int viewAngle = 0;
      socket.receive(&opcode, sizeof(opcode));
      if (opcode == PLAYER_POS_UPDATE) {
        socket.receive(&id, sizeof(id));
        socket.receive(&x, sizeof(x));
        socket.receive(&y, sizeof(y));
        if (players.find(id) != players.end()) {
          players[id]->goTo(x, y, 0);
        } else {
          players[id] = new Player();
        }
      }
    } catch (SocketException& e) {
      break;
    }
  }  
}
