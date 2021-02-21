#include "../includes/client.h"

#include "../includes/clientprotocol.h"
#include "../includes/drawablevector.h"
#include "../includes/log.h"
#include "../includes/scoreboard.h"
#include "../includes/startingscreen.h"
#include "../includes/configReader.h"
#include "../includes/playermap.h"
#include "../includes/Game.h"

#include <exception>

#define MAP_NOT_FOUND_ERROR "Error, map not found: "
#define COULD_NOT_CREATE_EXECUTER "Fatal error, the executer couldn't be created."
#define COULD_NOT_CREATE_SENDER "Fatal error, the sender couldn't be created."
#define MAX_NUMBER_OF_TEXTURES_PER_FRAME 100

static bool fileExists(std::string& name){
  if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void Client::connectToServer(std::string& ip, std::string& port) {
  this->socket.connect(ip, port);
}

void Client::buildWindow() {
  ConfigReader config("/usr/local/share/Wolfenstein/YAML/screenDimensions.yaml");
  int height = config.getHeight();
  int width = config.getWidth();

  this->window = new SdlWindow(width, height);

  if (window == NULL) {
    throw std::runtime_error("Can't build the window object.");
  }

  if (config.fullScreen()) {
    if (window->goFullScreen() != 0) {
      LOG(SDL_GetError());
    }
  }
}

Client::Client(SocketCommunication& socket, int myPlayerID) :
              socket(socket), myPlayerID(myPlayerID) {
  if (this->myPlayerID < 0){
    throw std::runtime_error("Can't have a negative player id.");
  }
  this->buildWindow();
}

Client::~Client() {
  delete this->window;
}

int Client::run(std::string& mapFile) {

  if (!fileExists(mapFile)){
    std::string error = MAP_NOT_FOUND_ERROR + mapFile;
    LOG(error.c_str());
    return ERROR;
  }

  Game game(this->socket, this->window, this->myPlayerID, mapFile);
  return game.start();
}
