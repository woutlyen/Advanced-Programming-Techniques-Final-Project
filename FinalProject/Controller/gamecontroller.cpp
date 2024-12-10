#include "gamecontroller.h"

#include <QTimer>
#include <iostream>
#include <unordered_map>

#include "View/worldview2d.h"
#include "View/worldviewtext.h"
#include "Model/worldrevised.h"

GameController::GameController(QObject *parent) : QObject(parent) {
    // Install the InputController as an event filter
    qApp->installEventFilter(&inputController);

    // Populate methodMap
    gamecontrollerMethodMap["up"] = [this]() {moveProtagonistUp();};
    gamecontrollerMethodMap["down"] = [this]() {moveProtagonistDown();};
    gamecontrollerMethodMap["left"] = [this]() {moveProtagonistLeft();};
    gamecontrollerMethodMap["right"] = [this]() {moveProtagonistRight();};



    // Connect InputController signals to GameController slots
    connect(&inputController, &InputController::upPressed, this, &GameController::moveProtagonistUp);
    connect(&inputController, &InputController::downPressed, this, &GameController::moveProtagonistDown);
    connect(&inputController, &InputController::leftPressed, this, &GameController::moveProtagonistLeft);
    connect(&inputController, &InputController::rightPressed, this, &GameController::moveProtagonistRight);

    connect(&inputController, &InputController::homePressed, this, &GameController::onHomePressed);
    connect(&inputController, &InputController::endPressed, this, &GameController::onEndPressed);

<<<<<<< HEAD
    connect(&inputController, &InputController::zoomChanged, this, &GameController::onZoomEvent);
    connect(&inputController, &InputController::shiftPressed, this, &GameController::changeViewMode);
    connect(&inputController, &InputController::enterPressed, this, &GameController::processCommand);
=======
    connect(&inputController, &InputController::zoomIn, this, &GameController::onZoomInEvent);
    connect(&inputController, &InputController::zoomOut, this, &GameController::onZoomOutEvent);
>>>>>>> subtask_E
}

void GameController::start()
{
    WorldRevised world;
    WorldViewText worldViewText;
    WorldView2D worldView2D;
    std::size_t gridSize{64};

    auto pro = world.getProtagonist();

    std::unique_ptr<Player> player = std::move(*reinterpret_cast<std::unique_ptr<Player>*>(&pro));

    world.createWorld(":/world_images/worldmap.png", 20, 5);
    tiles.push_back(world.getTiles());
    enemies.push_back(world.getEnemies());
    healthPacks.push_back(world.getHealthPacks());
    protagonist.push_back(std::move(player));
    width.push_back(world.getCols());
    heigth.push_back(world.getRows());

    protagonist.at(0)->setEnergy(10.0f);
    scenesText.push_back(worldViewText.makeScene(enemies.at(currentLevel), healthPacks.at(currentLevel), protagonist.at(currentLevel), heigth.at(currentLevel), width.at(currentLevel), ":/world_images/worldmap.png", gridSize));

    scenes2D.push_back(worldView2D.makeScene(enemies.at(currentLevel), healthPacks.at(currentLevel), protagonist.at(currentLevel), heigth.at(currentLevel), width.at(currentLevel), ":/world_images/worldmap.png", gridSize));
    currentLevel += 1;

    world.createWorld(":/world_images/worldmap.png", 5, 10);
    tiles.push_back(world.getTiles());
    enemies.push_back(world.getEnemies());
    healthPacks.push_back(world.getHealthPacks());
    pro = world.getProtagonist();
    player = std::move(*reinterpret_cast<std::unique_ptr<Player>*>(&pro));
    protagonist.push_back(std::move(player));
    width.push_back(world.getCols());
    heigth.push_back(world.getRows());

    scenesText.push_back(worldViewText.makeScene(enemies.at(currentLevel), healthPacks.at(currentLevel), protagonist.at(currentLevel), heigth.at(currentLevel), width.at(currentLevel), ":/world_images/worldmap.png", gridSize));

    scenes2D.push_back(worldView2D.makeScene(enemies.at(currentLevel), healthPacks.at(currentLevel), protagonist.at(currentLevel), heigth.at(currentLevel), width.at(currentLevel), ":/world_images/worldmap.png", gridSize));

    mainWindow.setScene(scenes2D.at(currentLevel));
    mainWindow.updateConnections(protagonist.at(currentLevel));
    mainWindow.show();

    /*
    QTimer* timer = new QTimer(this);
    timer->start(1000); // Trigger every 1000ms (1 second)
    */
}

void GameController::moveProtagonistUp() {
    static size_t pos{0};
    if (pos < enemies[0].size()){
        enemies[0].at(pos).get()->setDefeated(true);
        pos++;
    }

    if (!enemyController.checkForEnemy(enemies.at(currentLevel), protagonist.at(currentLevel), width.at(currentLevel), heigth.at(currentLevel), EnemyController::Position::Up)){
        playerController.moveUp(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel));
    }
}

void GameController::moveProtagonistDown() {
    if (!enemyController.checkForEnemy(enemies.at(currentLevel), protagonist.at(currentLevel), width.at(currentLevel), heigth.at(currentLevel), EnemyController::Position::Down)) {
        playerController.moveDown(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel), heigth.at(currentLevel));
    }
}

void GameController::moveProtagonistLeft() {
    if (!enemyController.checkForEnemy(enemies.at(currentLevel), protagonist.at(currentLevel), width.at(currentLevel), heigth.at(currentLevel), EnemyController::Position::Left)) {
        playerController.moveLeft(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel));
    }
}

void GameController::moveProtagonistRight() {
    if (!enemyController.checkForEnemy(enemies.at(currentLevel), protagonist.at(currentLevel), width.at(currentLevel), heigth.at(currentLevel), EnemyController::Position::Right)) {
        playerController.moveRight(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel));
    }
}

void GameController::onHomePressed() {
    currentLevel = 0;
<<<<<<< HEAD
    mainWindow.setScene(scenesText.at(currentLevel));
=======
    mainWindow.setScene(scenes2D.at(currentLevel));
    mainWindow.updateConnections(protagonist.at(currentLevel));
>>>>>>> subtask_E
}

void GameController::onEndPressed() {
    //currentLevel = 1;
    //mainWindow.setScene(scenesText.at(currentLevel));

    currentLevel = 0;
    mainWindow.setScene(scenes2D.at(currentLevel));
    mainWindow.updateConnections(protagonist.at(currentLevel));
}

void GameController::onZoomInEvent(){
    mainWindow.zoomIn();
}

void GameController::onZoomOutEvent(){
    mainWindow.zoomOut();
}

void GameController::changeViewMode() {
    switch (currentMode) {
        case TextView:
            currentMode = Graphics2DView;
            mainWindow.setScene(scenes2D.at(currentLevel));
            connect(&inputController, &InputController::upPressed, this, &GameController::moveProtagonistUp);
            connect(&inputController, &InputController::downPressed, this, &GameController::moveProtagonistDown);
            connect(&inputController, &InputController::leftPressed, this, &GameController::moveProtagonistLeft);
            connect(&inputController, &InputController::rightPressed, this, &GameController::moveProtagonistRight);
            break;

        case Graphics2DView:
            currentMode = TextView;
            mainWindow.setScene(scenesText.at(currentLevel));
            disconnect(&inputController, &InputController::upPressed, this, &GameController::moveProtagonistUp);
            disconnect(&inputController, &InputController::downPressed, this, &GameController::moveProtagonistDown);
            disconnect(&inputController, &InputController::leftPressed, this, &GameController::moveProtagonistLeft);
            disconnect(&inputController, &InputController::rightPressed, this, &GameController::moveProtagonistRight);
            break;
    }
}

void GameController::processCommand(QString textCommand) {

    // Ignore commands in 2D mode
    if (currentMode == Graphics2DView) return;

    // Check if the methodMap contains the command
    if (gamecontrollerMethodMap.find(textCommand.toStdString()) == gamecontrollerMethodMap.end()) return;

    // Exectute method mapped to textCommand
    gamecontrollerMethodMap[textCommand.toStdString()]();
}
