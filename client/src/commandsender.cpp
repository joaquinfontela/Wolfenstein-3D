#include "commandsender.h"

#include <SDL2/SDL.h>
#include <time.h>

#include <iostream>
#include "anglemanager.h"
#include "../../common/includes/protocol.h"
#include "player.h"

#define WIDTH 800
#define HEIGHT 600
#define DIMX 10
#define DIMY 13

CommandSender::CommandSender(SocketCommunication& s) : 
        socket(s), x(370), y(370) {
  this->update();
}

void CommandSender::update() {
  uint32_t protocol = PLAYER_POS_UPDATE;
  socket.send(&protocol, sizeof(protocol));
  socket.send(&x, sizeof(x));
  socket.send(&y, sizeof(y));
}

void CommandSender::run() {
  while (true) {
    try {
      int deltax = 0;
      int deltay = 0;
      int xmouse = 0;
      AngleManager angles;
      double viewAngle = angles.ANGLE270;

      SDL_Event event;
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT) {
        socket.readShutdown();
        socket.writeShutdown();
        socket.close();
        std::cout << "ESTOY MATANDO AL SENDER DE INFORMACIÓN." << std::endl;
        break;
      }
      this->update();
      if (event.type == SDL_KEYDOWN) {
        SDL_KeyboardEvent& key = (SDL_KeyboardEvent&)event;
        switch (key.keysym.sym) {
          case SDLK_a:
            if (x + 10 < DIMX * 64) deltax = 10; 
            break;
          case SDLK_d:
            if (x - 10 > 0) deltax = -10; 
            break;
          case SDLK_w:
            if (y + 10 < DIMY * 64) deltay = 10; 
            break;
          case SDLK_s:
            if (y - 10 > 0) deltay = -10; 
            break;
          case SDLK_LEFT:
            viewAngle -= angles.ANGLE10;
            if (viewAngle < 0) viewAngle += angles.ANGLE360;
            break;
          case SDLK_RIGHT:
            viewAngle -= angles.ANGLE10;
            if (viewAngle > angles.ANGLE360) viewAngle -= angles.ANGLE360;
            break;
        }
      } else if (event.type == SDL_MOUSEMOTION) {
        if (event.motion.x > xmouse) {
          viewAngle += angles.ANGLE1p5;
          if (viewAngle > angles.ANGLE360) viewAngle -= angles.ANGLE360;
        } else {
          viewAngle -= angles.ANGLE1p5;
          if (viewAngle < 0) viewAngle += angles.ANGLE360;
        }
        xmouse = event.motion.x;
      }

      double theta = viewAngle - angles.ANGLE270;
      if (theta < 0) theta += angles.ANGLE360;
      if (theta > angles.ANGLE360) theta -= angles.ANGLE360;
      x -= deltax * angles.fCos(theta) - deltay * angles.fSin(theta);
      y -= deltax * angles.fSin(theta) - deltay * angles.fCos(theta);

      this->update();
    } catch (SocketException& e) {
      break;
    }
  }
}
