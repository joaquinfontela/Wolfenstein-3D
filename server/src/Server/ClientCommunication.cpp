#include "../../includes/Server/ClientCommunication.h"

#include "../../../common/includes/Socket/SocketCommunication.h"
#include "../../../common/includes/Thread/Thread.h"

ClientCommunication::ClientCommunication(SocketCommunication peer,
                                         unsigned int id)
    : socket(std::move(peer)), playerID(id), running(true) {}

bool ClientCommunication::isAlive() { return running; }

void ClientCommunication::run() { running = false; }