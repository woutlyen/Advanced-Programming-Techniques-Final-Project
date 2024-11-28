#ifndef WORLDVIEWTEXT_H
#define WORLDVIEWTEXT_H

#include "View/statusbar2d.h"
#include "View/protagonistviewtext.h"
#include "world.h"
#include <QObject>
#include <QGraphicsScene>

class WorldViewText {
  public:
    WorldViewText();
    QGraphicsScene *makeScene(std::vector<std::unique_ptr<Enemy>> &enemies,
                              std::vector<std::unique_ptr<Tile>> &healthPacks,
                              std::unique_ptr<Protagonist> &protagonist,
                              int rows,
                              int columns,
                              QString filename = ":/world_images/worldmap.png",
                              std::size_t gridSize = 32);

  private:
    StatusBar2D *healthBar;
    StatusBar2D *energyBar;
};

#endif // WORLDVIEWTEXT_H
