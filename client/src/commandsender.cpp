#include "commandsender.h"

#include <SDL2/SDL.h>
#include <time.h>
#include <atomic>
#include <iostream>
#include "../../common/includes/protocol.h"

#define WIDTH 800
#define HEIGHT 600
#define DIMX 10
#define DIMY 13

#define UINT32_SIZE sizeof(uint32_t)

CommandSender::CommandSender(SocketCommunication& s, std::atomic<bool>& alive) : socket(s), alive(alive) {}

void CommandSender::update(uint32_t keyType) {

  socket.send(&keyType, UINT32_SIZE);

}

void CommandSender::run() {
  while (alive) {
    try {

      SDL_Event event;
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT) {
        uint32_t opcode = PLAYER_DISCONNECT;
        socket.send(&opcode, UINT32_SIZE);

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
