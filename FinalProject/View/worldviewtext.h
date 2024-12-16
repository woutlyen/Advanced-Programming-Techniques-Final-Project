#ifndef WORLDVIEWTEXT_H
#define WORLDVIEWTEXT_H

#include "Model/player.h"
#include "world.h"
#include <QObject>
#include <QGraphicsScene>

class WorldViewText {
  public:
    WorldViewText();
    QGraphicsScene *makeScene(std::vector<std::unique_ptr<Enemy>> &enemies,
                              std::vector<std::unique_ptr<Tile>> &healthPacks,
                              std::unique_ptr<Player> &protagonist,
                              int rows,
                              int columns,
                              QString filename = ":/world_images/worldmap.png",
                              std::size_t gridSize = 32);

  private:
    QColor darkGreen{0, 75, 0};  // Dark green color
    QColor lightGreen{144, 238, 144};  // Light green color

    QString pixmapToString(const QPixmap &pixmap);
    QPixmap recolorGrayscalePixmap(const QPixmap& pixmap);
};

#endif // WORLDVIEWTEXT_H
