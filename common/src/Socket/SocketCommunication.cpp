#include "../../includes/Socket/SocketCommunication.h"

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "../../includes/Socket/SocketException.h"

static int _getaddrinfo(struct addrinfo** serv_info, const char* hostname,
                        const char* port) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;

  int error = getaddrinfo(hostname, port, &hints, serv_info);

  if (error) {
    std::cerr << "getaddrinfo error" << std::endl;
  }

  return error;
}

SocketCommunication& SocketCommunication::operator=(
    SocketCommunication&& other) {
  if (this != &other) {
    this->fd = other.fd;
    other.fd = -1;
  }

  return *this;
}

SocketCommunication::SocketCommunication(SocketCommunication&& other) {
  // acá también hay que considerar si this es other
  this->fd = other.fd;
  other.fd = -1;
}

// Este método es bastante feo que sea público porque de alguna manera está rompiendo el encapsulamiento 
// del file descriptor. Tal vez un friend puede ayudar a que solamente una clase pueda usarlo y no cualquiera
// (pero no sé si friend se lleva bien con los constructores, la verdad...)
SocketCommunication::SocketCommunication(int fd) { this->fd = fd; }

void SocketCommunication::connect(const std::string& hostname,
                                  const std::string& port) {
  struct addrinfo* serv_info;

  if (_getaddrinfo(&serv_info, hostname.c_str(), port.c_str())) {
    throw SocketException();
  }

  struct addrinfo* head = serv_info;
  int connected = 0;

  for (; serv_info && !connected; serv_info = serv_info->ai_next) {
    int fd = socket(serv_info->ai_family, serv_info->ai_socktype,
                    serv_info->ai_protocol);
    if (::connect(fd, serv_info->ai_addr, serv_info->ai_addrlen) == -1) {
      ::close(fd);
    } else {
      connected = 1;
      this->fd = fd;
    }
  }

  freeaddrinfo(head);

  if (!connected) {
    throw SocketException();
  }

  return;
}

// Enviar y recibir tiras de  BYTES (uint8_t, char, unsigned char, lo que sea que ocupe 1B)
int SocketCommunication::send(const uint32_t* message,
                              unsigned int messageLength) {
  if (!message) {
    return 0;
  }

  unsigned int bytesSent = 0;
  int bytesPending = messageLength;

  while (bytesSent < messageLength) {
    int sent =
        ::send(this->fd, &message[bytesSent], bytesPending, MSG_NOSIGNAL);

    if (sent == -1) {
      throw SocketException();
    } else if (sent == 0) {
      break;
    }

    bytesSent += sent;
    bytesPending -= sent;
  }

  return bytesSent;
}

int SocketCommunication::sendDouble(const double* message,
                              unsigned int messageLength) {
  if (!message) {
    return 0;
  }

  unsigned int bytesSent = 0;
  int bytesPending = messageLength;

  while (bytesSent < messageLength) {
    int sent =
        ::send(this->fd, &message[bytesSent], bytesPending, MSG_NOSIGNAL);

    if (sent == -1) {
      throw SocketException();
    } else if (sent == 0) {
      break;
    }

    bytesSent += sent;
    bytesPending -= sent;
  }

  return bytesSent;
}

int SocketCommunication::receive(uint32_t* buffer, unsigned int bufLength) {
  if (bufLength == 0) {
    return 0;
  }

  int bytesAvailable = bufLength;
  int bytesReceived = 0;

  while (bytesReceived < bufLength) {
    int bytes = recv(this->fd, &buffer[bytesReceived], bytesAvailable, 0);

    if (bytes == -1) {
      throw SocketException();
    }

    if (bytes == 0) {
      throw SocketException();
    }

    bytesReceived += bytes;
    bytesAvailable -= bytes;
  }

  return bytesReceived;
}

int SocketCommunication::receiveDouble(double* buffer, unsigned int bufLength) {
  if (bufLength == 0) {
    return 0;
  }

  int bytesAvailable = bufLength;
  int bytesReceived = 0;

  while (bytesReceived < bufLength) {
    int bytes = recv(this->fd, &buffer[bytesReceived], bytesAvailable, 0);

    if (bytes == -1) {
      throw SocketException();
    }

    if (bytes == 0) {
      throw SocketException();
    }

    bytesReceived += bytes;
    bytesAvailable -= bytes;
  }

  return bytesReceived;
}

void SocketCommunication::writeShutdown() { shutdown(this->fd, SHUT_WR); }

void SocketCommunication::readShutdown() { shutdown(this->fd, SHUT_RD); }

void SocketCommunication::close() {
  ::close(this->fd);
  this->fd = -1;
}

SocketCommunication::~SocketCommunication() {
  if (this->fd != -1) {
    ::close(this->fd);
  }
}
