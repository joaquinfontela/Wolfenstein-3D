#ifndef __MATCH_H__
#define __MATCH_H__

#include <atomic>
#include <list>
#include <map>
#include <queue>

#include "../Model/Game/Game.h"
#include "../../../common/includes/Queue/WaitingQueue.h"
#include "../Control/Command/Command.h"
#include "../Control/Notification/Notification.h"
#include "../Server/ClientCommunication.h"
#include "../Server/ConnectionHandler.h"
#include "Engine.h"

class Engine;
class ClientCommunication;


class Match {
 private:
  std::atomic<bool> cont;
  Engine* engine;
  WaitingQueue<Command*> commands;
  WaitingQueue<Notification*> notis;
  Game game;

  int ID;
  int mapID;
  unsigned int playerCount;
  bool running;
  std::map<int, ClientCommunication*> players;

 public:
  Match();
  ~Match();
  Match(int lobbyID, std::string mapFile, int mapID);
  explicit Match(int lobbyID);

  /**
    * <Forces the shutdown of the match>
  */
  void forceShutdown();

  /** 
    * <Returns if the game has certain id>
    *
    * @param ID to check.
    * @return True if match has given ID.
  */
  bool hasID(int lobbyID);

  /**
    * <Starts the match.>
  */
  void start();

  /**
    * <Checks if the game has ended.>
    *
    * @return True if match has ended.
  */
  bool hasEnded();

  /**
    * <Adds a player to the given match if possible>
    *
    * @param The ClientCommunication of the player.
    * @return The ConnectionHandler for that player, NULL if not possible
  */
  ConnectionHandler* addPlayerToMatch(ClientCommunication* player);

  int getMapID();

  bool isJoinable();
};

#endif
