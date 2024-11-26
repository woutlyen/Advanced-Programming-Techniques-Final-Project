#ifndef WORLDVIEWTEXT_H
#define WORLDVIEWTEXT_H

#include "qgraphicsscene.h"
#include "world.h"

class WorldViewText
{
public:
    WorldViewText();
    QGraphicsScene* makeScene(std::vector<std::unique_ptr<Enemy>>& enemies,
                              std::vector<std::unique_ptr<Tile>>& healthPacks,
                              std::unique_ptr<Protagonist>& protagonist,
                              int rows,
                              int columns,
                              QString filename = ":/world_images/worldmap.png",
                              std::size_t gridSize = 32);
};

#endif // WORLDVIEWTEXT_H
