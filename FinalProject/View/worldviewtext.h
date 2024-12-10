#ifndef WORLDVIEWTEXT_H
#define WORLDVIEWTEXT_H

#include "Model/player.h"
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
                              std::unique_ptr<Player> &protagonist,
                              int rows,
                              int columns,
                              QString filename = ":/world_images/worldmap.png",
                              std::size_t gridSize = 32);

  private:
    StatusBar2D *healthBar;
    StatusBar2D *energyBar;

    QColor darkGreen{0, 50, 0};  // Dark green color
    QColor lightGreen{144, 238, 144};  // Light green color

    QString pixmapToString(const QPixmap &pixmap);
    QPixmap recolorGrayscalePixmap(const QPixmap& pixmap);
};

#endif // WORLDVIEWTEXT_H
