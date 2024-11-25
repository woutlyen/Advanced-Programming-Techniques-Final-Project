#include "gamecontroller.h"

#include <QGraphicsScene>

#include "View/worldview2d.h"
GameController::GameController() {
    // Install the InputController as an event filter
    qApp->installEventFilter(&inputController);

}

void GameController::start()
{
    World world;
    world.createWorld(":/world_images/worldmap.png", 5, 10);

    tiles = world.getTiles();
    enemies = world.getEnemies();
    healthPacks = world.getHealthPacks();
    protagonist = world.getProtagonist();

    QGraphicsScene* scene;
    WorldView2D worldView2D;
    std::size_t gridSize {32};
    scene = worldView2D.makeScene(enemies, healthPacks, protagonist, ":/world_images/worldmap.png",gridSize);

    mainWindow.setScene(scene);
    mainWindow.show();
}
