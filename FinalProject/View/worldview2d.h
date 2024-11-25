#ifndef WORLDVIEW2D_H
#define WORLDVIEW2D_H

#include "worldview.h"

class WorldView2D : public WorldView
{
public:
    WorldView2D();
    QGraphicsScene* makeScene(std::vector<std::unique_ptr<Enemy>>& enemies,
                              std::vector<std::unique_ptr<Tile>>& healthPacks,
                              std::unique_ptr<Protagonist>& protagonist,
                              QString filename,
                              std::size_t gridSize);
};

#endif // WORLDVIEW2D_H
