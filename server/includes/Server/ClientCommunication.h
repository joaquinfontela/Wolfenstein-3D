#ifndef __CLIENT_COMMUNICATION_H__
#define __CLIENT_COMMUNICATION_H__

#include "../../../common/includes/Socket/SocketCommunication.h"
#include "../../../common/includes/Thread/Thread.h"
#include "../Match/MatchList.h"

class ClientCommunication : public Thread {
 private:
  SocketCommunication socket;
  unsigned int playerID;
  MatchList& matchList;
  bool running;

  void connectToLobby();

  // TODO -> Aca va una queue de comandos, cada vez que recibe un comando lo
  // pusheo aca.
  // TODO -> Aca iria un Queue de Notificaciones, debo enviar todas las
  // notificaciones a cada cliente por cada iteracion.

 public:
  ClientCommunication(SocketCommunication peer, unsigned int id,
                      MatchList& matches);

  unsigned int ID();
  bool isAlive();

  void run();
};

#endif