#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <mutex>
#include <vector>
#include "../player.h"
#include "../drawable.h"
#include "../../../common/includes/Map/Map.h"

namespace Lua{

class GameState{
private:
    std::mutex lock;                      // Lock para actualizar/leer desde multiples hilos de forma segura.
    Map& matrix;                          // Representacion Matricial del mapa.
    Player* selfPlayer;                   // Jugador representado por el script de Lua.
    std::vector<Drawable*> seenObjects;   // Vector de objetos que pueden ser observados por el jugador en ese momento

public:
    // Devuelve true si tiene un jugador al alcance de su vista.
    bool playerInSight();

    // Devuelve true si el jugador tiene al alcance de interaccion una puerta.
    bool facingDoor();

    // Devuelve true si el jugador esta proximo a colisionar con una pared en la direccion que esta mirando.
    bool facingWall();

    // Devuelve True si el jugador tiene un item al alcance de su vista.
    bool itemInSight();

    // Aca podria agregar otros tipos de chequeos booleanos para decidir.
};


}


#endif
