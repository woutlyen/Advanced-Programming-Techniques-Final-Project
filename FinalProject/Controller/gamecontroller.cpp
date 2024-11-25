#include "gamecontroller.h"

#include <QGraphicsScene>
#include <QTimer>
#include <iostream>

#include "View/worldview2d.h"

GameController::GameController(QObject *parent) : QObject(parent) {
    // Install the InputController as an event filter
    qApp->installEventFilter(&inputController);

    // Connect InputController signals to GameController slots
    connect(&inputController, &InputController::upPressed, this, &GameController::onUpPressed);
    connect(&inputController, &InputController::downPressed, this, &GameController::onDownPressed);
    connect(&inputController, &InputController::leftPressed, this, &GameController::onLeftPressed);
    connect(&inputController, &InputController::rightPressed, this, &GameController::onRightPressed);

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

    /*
    QTimer* timer = new QTimer(this);
    timer->start(1000); // Trigger every 1000ms (1 second)
    */
}

void GameController::onUpPressed() {
    std::cout << "Up" << std::endl;
}

void GameController::onDownPressed() {
    std::cout << "Down" << std::endl;
}

void GameController::onLeftPressed() {
    std::cout << "Left" << std::endl;
}

void GameController::onRightPressed() {
    std::cout << "Right" << std::endl;
}

