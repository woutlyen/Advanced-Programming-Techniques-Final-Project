#ifndef WORLDVIEW2D_H
#define WORLDVIEW2D_H

#include "statusbar2d.h"

#include <QPixmap>
#include <QColor>

class WorldView2D :
{
public:
    WorldView2D();
    QGraphicsScene* makeScene(std::vector<std::unique_ptr<Enemy>>& enemies,
                              std::vector<std::unique_ptr<Tile>>& healthPacks,
                              std::unique_ptr<Protagonist>& protagonist,
                              int rows,
                              int columns,
                              QString filename = ":/world_images/worldmap.png",
                              std::size_t gridSize = 32);

private:
    QPixmap recolorGrayscalePixmap(const QPixmap& pixmap);
    QColor darkGreen{0, 50, 0};  // Dark green color
    QColor lightGreen{144, 238, 144};  // Light green color

    StatusBar2D* healthBar;
    StatusBar2D* energyBar;
};

#endif // WORLDVIEW2D_H
