#ifndef __CLIENT_ACCEPTER_H__
#define __CLIENT_ACCEPTER_H__

#include <list>

#include "../../../common/includes/Socket/SocketListener.h"
#include "../../../common/includes/Thread/Thread.h"
#include "../Match/MatchList.h"
#include "ClientCommunication.h"

class ClientAccepter : public Thread {
 private:
  SocketListener& socket;
  MatchList& matchList;
  std::list<ClientCommunication*> peers;
  void clientCleanup();

 public:
  ClientAccepter(SocketListener& sock, MatchList& matchList);
  void run();
};

#endif