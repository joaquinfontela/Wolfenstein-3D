#ifndef __SOCKET_COMMUNICATION_H__
#define __SOCKET_COMMUNICATION_H__
#include <string>
#include "SocketListener.h"

class SocketListener;

class SocketCommunication {
 private:
  int fd;

 public:
  // Crea el socket con el file descriptor dado.
  SocketCommunication();
  SocketCommunication(SocketListener& listener);
  SocketCommunication(SocketCommunication&& other);

  SocketCommunication& operator=(SocketCommunication&& other);

  // Conecta el socket al host y puerto dado.
  void connect(const std::string& hostname, const std::string& port);

  // Envia un mensaje de tamaño messageLength. Devuelve la cantidad de bytes
  // enviados.
  int send(const char* message, unsigned int messageLength);

  // Recibe un mensaje y lo almacena en el buffer. Devuelve la cantidad de bytes
  // leidos.
  int receive(char* buffer, unsigned int bufLength);

  // Cierra el canal de escritura del socket.
  void writeShutdown();

  // Cierra el canal de lectura del socket.
  void readShutdown();

  // Cierra el socket.
  void close();

  ~SocketCommunication();
};

#endif
