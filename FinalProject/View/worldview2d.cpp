#include "worldview2d.h"

#include "Controller/levelcontroller.h"
#include "Model/xenemy.h"

#include "View/enemyview2d.h"
#include "View/penemyview2d.h"
#include "View/xenemyview2d.h"

#include "View/healthpackview2d.h"
#include "View/protagonistview2d.h"

#include <QGraphicsScene>


QGraphicsScene *WorldView2D::makeScene() const
{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();

    QGraphicsScene* scene = new QGraphicsScene();

    QGraphicsPixmapItem* map = scene->addPixmap(QPixmap(level.visual_map));
    map->setScale(level.grid_size/level.visual_grid_size);
    map->setZValue(-1);

    // Create and add health views
    for (const auto& healthPack : level.healthPacks) {
        scene->addItem(new HealthPackView2D(healthPack,level.grid_size));
    }

    // Create and add enemy views
    for (const auto& enemy : level.enemies) {

        if (dynamic_cast<PEnemyWrapper*>(enemy.get())) {
            // If the enemy is of type PEnemy
            scene->addItem(new PEnemyView2D(enemy, level.grid_size));
        } else if (dynamic_cast<XEnemy*>(enemy.get())) {
            // If the enemy is of type XEnemy
            scene->addItem(new XEnemyView2D(enemy, level.grid_size));
        } else {
            // If the enemy is of type Enemy
            scene->addItem(new EnemyView2D(enemy, level.grid_size));
        }
    }


    // Create and add protagonist view
    scene->addItem(new ProtagonistView2D(level.protagonist,level.grid_size));

    return scene;

}

QGraphicsEllipseItem* WorldView2D::addPoisonCircle(int x, int y, int radius,QGraphicsScene* scene, int value)
{
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(x - radius/3, y - radius/3, radius, radius);

    ellipse->setBrush(QColor(83, 0, 128, (value*255)/(100)));
    ellipse->setPen(Qt::NoPen);
    ellipse->setZValue(-0.5);
    scene->addItem(ellipse);

    return ellipse;
}

void WorldView2D::removePoisonCircle(QGraphicsEllipseItem *poisonCircle, QGraphicsScene *scene)
{
    scene->removeItem(poisonCircle);
    delete poisonCircle;
}
