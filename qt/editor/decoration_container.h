#ifndef DECORATION_CONTAINER_H
#define DECORATION_CONTAINER_H

#include "tiles_container.h"

class decoration_container : public tiles_container
{
    tile* tile_clicked(int x, int y) override;
public:
    decoration_container();
};

#endif // DECORATION_CONTAINER_H
