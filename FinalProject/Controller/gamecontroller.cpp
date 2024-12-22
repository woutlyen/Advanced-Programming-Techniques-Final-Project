#include "gamecontroller.h"
#include "Controller/levelcontroller.h"

#include <QTimer>
#include <unordered_map>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

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

    connect(&inputController, &InputController::shiftPressed, this, &GameController::changeViewMode);
    connect(&inputController, &InputController::enterPressed, this, &GameController::processCommand);

    connect(&inputController, &InputController::zoomIn, this, &GameController::onZoomInEvent);
    connect(&inputController, &InputController::zoomOut, this, &GameController::onZoomOutEvent);

}

void GameController::start(QString& filePath)
{
    LevelController& levelController = LevelController::getInstance();
    levelController.initializeLevels(filePath);

    mainWindow.setScene();
    mainWindow.updateConnections();
    mainWindow.show();
    playerController.moveRight();
}

bool GameController::checkForPrevLevel()
{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();

    if(level.protagonist->getXPos() == level.prev_level_x_pos && level.protagonist->getYPos() == level.prev_level_y_pos){
        levelController.setCurrentLevelNr(levelController.getCurrentLevelNr() -1);
        mainWindow.setScene();
        mainWindow.updateConnections();
        return true;
    }
    return false;
}

bool GameController::checkForNextLevel()
{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();

    if(level.protagonist->getXPos() == level.next_level_x_pos && level.protagonist->getYPos() == level.next_level_y_pos){
        levelController.setCurrentLevelNr(levelController.getCurrentLevelNr() +1);
        mainWindow.setScene();
        mainWindow.updateConnections();
        return true;
    }
    return false;
}

void GameController::moveProtagonistUp() {
    if (!enemyController.checkForEnemy(EnemyController::Position::Up)){
        playerController.moveUp();
        playerController.checkForHealthPack();
        if (checkForPrevLevel() || checkForNextLevel()){
            playerController.moveUp();
        }
    }
}

void GameController::moveProtagonistDown() {
    if (!enemyController.checkForEnemy(EnemyController::Position::Down)) {
        playerController.moveDown();
        playerController.checkForHealthPack();
        if (checkForPrevLevel() || checkForNextLevel()){
            playerController.moveDown();
        }
    }
}

void GameController::moveProtagonistLeft() {
    if (!enemyController.checkForEnemy(EnemyController::Position::Left)) {
        playerController.moveLeft();
        playerController.checkForHealthPack();
        if (checkForPrevLevel() || checkForNextLevel()){
            playerController.moveLeft();
        }
    }
}

void GameController::moveProtagonistRight() {
    if (!enemyController.checkForEnemy(EnemyController::Position::Right)) {
        playerController.moveRight();
        playerController.checkForHealthPack();
        if (checkForPrevLevel() || checkForNextLevel()){
            playerController.moveRight();
        }
    }
}

void GameController::onHomePressed() {
}

void GameController::onEndPressed() {
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
            //mainWindow.setScene(scenes2D.at(currentLevel));
            connect(&inputController, &InputController::upPressed, this, &GameController::moveProtagonistUp);
            connect(&inputController, &InputController::downPressed, this, &GameController::moveProtagonistDown);
            connect(&inputController, &InputController::leftPressed, this, &GameController::moveProtagonistLeft);
            connect(&inputController, &InputController::rightPressed, this, &GameController::moveProtagonistRight);
            break;

        case Graphics2DView:
            currentMode = TextView;
            //mainWindow.setScene(scenesText.at(currentLevel));
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
