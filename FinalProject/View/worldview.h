#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include "world.h"

#include <QGraphicsScene>

class WorldView : public QGraphicsScene
{
public:
    WorldView();
    virtual QGraphicsScene* makeScene(std::vector<std::unique_ptr<Enemy>>& enemies,
                                      std::vector<std::unique_ptr<Tile>>& healthPacks,
                                      std::unique_ptr<Protagonist>& protagonist,
                                      QString filename,
                                      std::size_t gridSize) = 0;

};

#endif // WORLDVIEW_H
