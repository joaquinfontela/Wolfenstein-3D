#ifndef __SERVER_H__
#define __SERVER_H__

#include "../../../common/includes/Socket/SocketListener.h"

class Server {
 private:
  SocketListener listener;

 public:
  Server(const std::string& port);
  int run();
};

#endif