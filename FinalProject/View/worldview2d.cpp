#include "worldview2d.h"

#include "View/enemyview2d.h"
#include "View/healthpackview2d.h"
#include "View/protagonistview2d.h"

WorldView2D::WorldView2D() {}

QGraphicsScene *WorldView2D::makeScene(std::vector<std::unique_ptr<Enemy> > &enemies, std::vector<std::unique_ptr<Tile> > &healthPacks, std::unique_ptr<Protagonist> &protagonist, QString filename, std::size_t gridSize)
{
    scene = new QGraphicsScene();

    scene->addPixmap(QPixmap(filename)
                         .scaled(gridSize*QPixmap(filename).width(),
                                 gridSize*QPixmap(filename).height(),
                                 Qt::KeepAspectRatio));

    // Create and add health views
    for (const auto& healthPack : healthPacks) {
        scene->addItem(new HealthPackView2D(healthPack,gridSize));
    }

    // Create and add enemy views
    for (const auto& enemy : enemies) {
        //TODO seperate enemies
        scene->addItem(new EnemyView2D(enemy,gridSize));
    }

    // Create and add protagonist view
    scene->addItem(new ProtagonistView2D(protagonist,gridSize));

    return scene;
}
