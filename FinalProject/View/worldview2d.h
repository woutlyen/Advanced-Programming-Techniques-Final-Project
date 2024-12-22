#ifndef WORLDVIEW2D_H
#define WORLDVIEW2D_H

#include "Model/player.h"
#include "world.h"
#include <QObject>
#include <QPixmap>
#include <QColor>
#include <QGraphicsScene>

class WorldView2D: public QObject
{
public:
    WorldView2D();
    QGraphicsScene* makeScene(std::vector<std::unique_ptr<Enemy>>& enemies,
                              std::vector<std::unique_ptr<Tile>>& healthPacks,
                              std::unique_ptr<Player>& protagonist,
                              int rows,
                              int columns,
                              QString filename = ":/world_images/worldmap.png",
                              std::size_t gridSize = 32,
                              std::size_t imageGridSize = 32);

    QGraphicsScene* makeScene();

private:
    QPixmap recolorGrayscalePixmap(const QPixmap& pixmap);
    QColor darkGreen{0, 50, 0};  // Dark green color
    QColor lightGreen{144, 238, 144};  // Light green color
};

#endif // WORLDVIEW2D_H
