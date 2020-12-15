#ifndef __MAP_H__
#define __MAP_H__

#include "../Player/Player.h"
class Map{

private:

    int map[10][10]; // Esto deberia determinarse dinamicamente, considerar memoria dinamica.


public:

    bool checkCollision(int toX, int toY);

    void respawn(Player& player);

};






#endif