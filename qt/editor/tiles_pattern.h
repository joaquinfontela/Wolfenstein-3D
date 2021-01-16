#ifndef TILES_PATTERN_H
#define TILES_PATTERN_H

#include "list"
#include "tile.h"


class tiles_pattern
{
    std::list<tile> tiles;
public:
    tiles_pattern();
    void update_pattern(QFrame conteiner);
};

#endif // TILES_PATTERN_H
