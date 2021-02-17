#ifndef __SOCKET_LISTENER_H__
#define __SOCKET_LISTENER_H__

#include <string>

#include "SocketCommunication.h"

class SocketCommunication;

class SocketListener {
 private:
  int fd;

 public:
  SocketListener();
  // Bindea el socket al puerto determinado.
  void bind(const std::string& port);

  // Acepta un cliente y devuelve un socket con el fd correspondiente al cliente
  // aceptado.
  int _accept();

  // Cierra el servidor
  void close();

  ~SocketListener();
};

#endif
