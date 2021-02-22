#include "../includes/commandsender.h"

#include <SDL2/SDL.h>
#include <time.h>

#include <atomic>
#include <iostream>

#include "../../common/includes/protocol.h"
#include "../includes/clientprotocol.h"
#include "../includes/startingscreen.h"
#include "../includes/scoreboard.h"
#include "../includes/player.h"

#define UINT32_SIZE sizeof(uint32_t)

CommandSender::CommandSender(SocketCommunication& s, std::atomic<bool>& alive,
                             ScoreBoard* scoreboard, Player* player, StartingScreen* startingscreen)
    : CommandManager(scoreboard, s, alive), player(player), startingscreen(startingscreen) {}

void CommandSender::update(uint32_t keyType) {
  socket.send(keyType);
}

void CommandSender::run() {
  bool upPressed = false;
  bool downPressed = false;
  bool rightPressed = false;
  bool leftPressed = false;
  bool enterPressed = false;
  while (true) {
    try {
      SDL_Event event;
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT) {
        uint32_t opcode = PLAYER_DISCONNECT;
        socket.send(opcode);
        socket.getSocket().readShutdown();
        socket.getSocket().writeShutdown();
        socket.getSocket().close();
        alive = false;
        this->scoreboard->stop();
        this->startingscreen->stop();
        break;
      }
      if (event.type == SDL_KEYDOWN && alive) {
        SDL_KeyboardEvent& key = (SDL_KeyboardEvent&)event;
        switch (key.keysym.sym) {
          case SDLK_a:
            if (!leftPressed) {
              leftPressed = true;
              this->update(KEY_A_DOWN);
            }
            break;
          case SDLK_d:
            if (!rightPressed) {
              rightPressed = true;
              this->update(KEY_D_DOWN);
            }
            break;
          case SDLK_w:
            if (!upPressed) {
              upPressed = true;
              this->update(KEY_W_DOWN);
            }
            break;
          case SDLK_s:
            if (!downPressed) {
              downPressed = true;
              this->update(KEY_S_DOWN);
            }
            break;
          case SDLK_RETURN:
            if (!enterPressed) {
              enterPressed = true;
              this->update(PLAYER_SHOOT_DOWN);
            }
            break;
          case SDLK_e:
            this->update(OPEN_DOOR);
            break;
          case SDLK_1:
            this->update(KEY_1_DOWN);
            break;
          case SDLK_2:
            this->update(KEY_2_DOWN);
            break;
          case SDLK_3:
            this->update(KEY_3_DOWN);
            break;
          case SDLK_4:
            this->update(KEY_4_DOWN);
            break;
          case SDLK_5:
            this->update(KEY_5_DOWN);
            break;
          case SDLK_p:
            this->update(START_MATCH);
            break;
        }
      } else if (event.type == SDL_KEYUP && alive) {
        SDL_KeyboardEvent& key = (SDL_KeyboardEvent&)event;
        switch (key.keysym.sym) {
          case SDLK_a:
            leftPressed = false;
            this->update(KEY_A_UP);
            break;
          case SDLK_d:
            rightPressed = false;
            this->update(KEY_D_UP);
            break;
          case SDLK_w:
            upPressed = false;
            this->update(KEY_W_UP);
            break;
          case SDLK_s:
            downPressed = false;
            this->update(KEY_S_UP);
            break;
          case SDLK_RETURN:
            enterPressed = false;
            this->update(PLAYER_SHOOT_UP);
            if (this->player)
              this->player->minigunShooting = false;
            break;
          case SDLK_LEFT:
            break;
          case SDLK_RIGHT:
            break;
        }
      }
    } catch (std::exception& e) {
      LOG(e.what());
      break;
    }
  }
}
