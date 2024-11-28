#include "gamecontroller.h"

#include <QTimer>

#include "View/worldview2d.h"
#include "View/worldviewtext.h"

GameController::GameController(QObject *parent) : QObject(parent) {
    // Install the InputController as an event filter
    qApp->installEventFilter(&inputController);

    // Connect InputController signals to GameController slots
    connect(&inputController, &InputController::upPressed, this, &GameController::onUpPressed);
    connect(&inputController, &InputController::downPressed, this, &GameController::onDownPressed);
    connect(&inputController, &InputController::leftPressed, this, &GameController::onLeftPressed);
    connect(&inputController, &InputController::rightPressed, this, &GameController::onRightPressed);

    connect(&inputController, &InputController::homePressed, this, &GameController::onHomePressed);
    connect(&inputController, &InputController::endPressed, this, &GameController::onEndPressed);

}

void GameController::start()
{
    World world;
    WorldViewText worldViewText;
    std::size_t gridSize {64};

    world.createWorld(":/world_images/worldmap.png", 20, 5);
    tiles.push_back(world.getTiles());
    enemies.push_back(world.getEnemies());
    healthPacks.push_back(world.getHealthPacks());
    protagonist.push_back(world.getProtagonist());
    width.push_back(world.getCols());
    heigth.push_back(world.getRows());

    protagonist.at(0)->setEnergy(10.0f);
    scenesText.push_back(worldViewText.makeScene(enemies.at(currentLevel), healthPacks.at(currentLevel), protagonist.at(currentLevel), heigth.at(currentLevel) , width.at(currentLevel), ":/world_images/worldmap.png",gridSize));
    currentLevel += 1;

    world.createWorld(":/world_images/worldmap.png", 5, 10);
    tiles.push_back(world.getTiles());
    enemies.push_back(world.getEnemies());
    healthPacks.push_back(world.getHealthPacks());
    protagonist.push_back(world.getProtagonist());
    width.push_back(world.getCols());
    heigth.push_back(world.getRows());

    scenesText.push_back(worldViewText.makeScene(enemies.at(currentLevel), healthPacks.at(currentLevel), protagonist.at(currentLevel), heigth.at(currentLevel) , width.at(currentLevel), ":/world_images/worldmap.png",gridSize));


    mainWindow.setScene(scenesText.at(currentLevel));
    mainWindow.show();

    /*
    QTimer* timer = new QTimer(this);
    timer->start(1000); // Trigger every 1000ms (1 second)
    */
}

void GameController::onUpPressed() {
    if (!enemyController.checkForEnemy(enemies.at(currentLevel), protagonist.at(currentLevel), width.at(currentLevel), heigth.at(currentLevel), EnemyController::Position::Up)){
        playerController.moveUp(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel));
    }
}

void GameController::onDownPressed() {
    if (!enemyController.checkForEnemy(enemies.at(currentLevel), protagonist.at(currentLevel), width.at(currentLevel), heigth.at(currentLevel), EnemyController::Position::Down)){
        playerController.moveDown(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel), heigth.at(currentLevel));
    }
}

void GameController::onLeftPressed() {
    if (!enemyController.checkForEnemy(enemies.at(currentLevel), protagonist.at(currentLevel), width.at(currentLevel), heigth.at(currentLevel), EnemyController::Position::Left)){
        playerController.moveLeft(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel));
    }
}


void GameController::onRightPressed() {
    if (!enemyController.checkForEnemy(enemies.at(currentLevel), protagonist.at(currentLevel), width.at(currentLevel), heigth.at(currentLevel), EnemyController::Position::Right)){
        playerController.moveRight(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel));
    }
}

void GameController::onHomePressed() {
    currentLevel = 0;
    mainWindow.setScene(scenesText.at(currentLevel));
}


void GameController::onEndPressed() {
    currentLevel = 1;
    mainWindow.setScene(scenesText.at(currentLevel));
}



