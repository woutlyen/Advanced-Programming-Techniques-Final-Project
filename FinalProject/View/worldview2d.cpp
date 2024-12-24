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

    scene->addPixmap(QPixmap(level.visual_map))->setScale(level.grid_size/level.visual_grid_size);

    // Create and add health views
    for (const auto& healthPack : level.healthPacks) {
        scene->addItem(new HealthPackView2D(healthPack,level.grid_size));
    }

    // Create and add enemy views
    for (const auto& enemy : level.enemies) {

        if (dynamic_cast<PEnemy*>(enemy.get())) {
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
