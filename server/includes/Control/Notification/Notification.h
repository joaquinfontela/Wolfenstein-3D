#ifndef __NOTIFICATION_H__
#define __NOTIFICATION_H__
#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "../../../../common/includes/Socket/SocketWrapper.h"

/**
  * @section DESCRIPTION
  * The class that represents a notifiable event to be sent to the clients.
*/
class Notification {
 public:

  /**
    * <Sends the notification through the specified socket.>
    *
    * @param The socket required to send the notification
  */
  virtual void send(SocketWrapper& socket) = 0;
  virtual ~Notification(){};
};

#endif
