#include "commandsender.h"

#include <SDL2/SDL.h>
#include <time.h>

#include <iostream>
#include "anglemanager.h"
#include "../../common/includes/protocol.h"

#define WIDTH 800
#define HEIGHT 600
#define DIMX 10
#define DIMY 13

#define KEY_A_DOWN 100
#define KEY_D_DOWN 200
#define KEY_W_DOWN 300
#define KEY_S_DOWN 400
#define KEY_A_UP 500
#define KEY_D_UP 600
#define KEY_W_UP 700
#define KEY_S_UP 800

CommandSender::CommandSender(SocketCommunication& s, std::atomic<bool>& alive) : socket(s), alive(alive) {}

void CommandSender::update(uint32_t keyType) {
  uint32_t protocol = PLAYER_POS_UPDATE;
  socket.send(&protocol, sizeof(protocol));
  //socket.send(&keyType, sizeof(keyType));
}

void CommandSender::run() {
  while (alive) {
    try {
      SDL_Event event;
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT) {
        socket.readShutdown();
        socket.writeShutdown();
        socket.close();
        alive = false;
        break;
      }
      if (event.type == SDL_KEYDOWN) {
        SDL_KeyboardEvent& key = (SDL_KeyboardEvent&)event;
        switch (key.keysym.sym) {
          case SDLK_a:
            this->update(KEY_A_DOWN);
            break;
          case SDLK_d:
            this->update(KEY_D_DOWN);
            break;
          case SDLK_w:
            this->update(KEY_W_DOWN);
            break;
          case SDLK_s:
            this->update(KEY_S_DOWN);
            break;
          case SDLK_LEFT:
            break;
          case SDLK_RIGHT:
            break;
        }
      } else if (event.type == SDL_KEYUP) {
        SDL_KeyboardEvent& key = (SDL_KeyboardEvent&)event;
        switch (key.keysym.sym) {
          case SDLK_a:
            this->update(KEY_A_UP);
            break;
          case SDLK_d:
            this->update(KEY_D_UP);
            break;
          case SDLK_w:
            this->update(KEY_W_UP);
            break;
          case SDLK_s:
            this->update(KEY_S_UP);
            break;
          case SDLK_LEFT:
            break;
          case SDLK_RIGHT:
            break;
        }
      }

    } catch (SocketException& e) {
      break;
    }
  }
}
