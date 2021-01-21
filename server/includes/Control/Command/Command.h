#ifndef __COMMAND_H__
#define __COMMAND_H__


#include "../../Model/Game/Game.h"
#include "../../../../common/includes/Queue/WaitingQueue.h"
#include "../Notification/Notification.h"

class ClientCommunication;

/**
  * @section DESCRIPTION	
  * The class that represents a player intent in the game.
*/
class Command {
 public:

  /**
	* <Executes the given command>
	*
	* @param Queue of Notifications to be sent.
	* @param The game on which to execute the given command.

  */
  virtual void execute(WaitingQueue<Notification*>& notifications, Game& game) = 0;
  virtual ~Command(){};
};

#endif
