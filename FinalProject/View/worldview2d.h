#ifndef WORLDVIEW2D_H
#define WORLDVIEW2D_H

#include "statusbar2d.h"
#include "worldview.h"

#include <QPixmap>
#include <QColor>

class WorldView2D : public WorldView
{
public:
    WorldView2D();
    QGraphicsScene* makeScene(std::vector<std::unique_ptr<Enemy>>& enemies,
                              std::vector<std::unique_ptr<Tile>>& healthPacks,
                              std::unique_ptr<Protagonist>& protagonist,
                              QString filename,
                              std::size_t gridSize);

private:
    QPixmap recolorGrayscalePixmap(const QPixmap& pixmap);
    QColor darkGreen{0, 50, 0};  // Dark green color
    QColor lightGreen{144, 238, 144};  // Light green color

    StatusBar2D* healthBar;
    StatusBar2D* energyBar;
};

#endif // WORLDVIEW2D_H
