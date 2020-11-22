#ifndef __SOCKET_LISTENER_H__
#define __SOCKET_LISTENER_H__

#include <string>

#include "SocketCommunication.h"

class SocketListener {
 private:
  int fd;

 public:
  SocketListener();
  // Bindea el socket al puerto determinado.
  void bind(const std::string& port);

  // Acepta un cliente y devuelve un socket con el fd correspondiente al cliente
  // aceptado.
  SocketCommunication accept();

  // Cierra el servidor
  void close();

  ~SocketListener();
};

#endif