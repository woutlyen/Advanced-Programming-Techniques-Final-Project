 #include "gamecontroller.h"
#include "Controller/levelcontroller.h"

GameController::GameController(QObject *parent) : QObject(parent) {
    // Install the InputController as an event filter
    qApp->installEventFilter(&inputController);

    // Connect InputController signals to GameController slots
    connect(&inputController, &InputController::zoomIn, this, &GameController::onZoomInEvent);
    connect(&inputController, &InputController::zoomOut, this, &GameController::onZoomOutEvent);

}

void GameController::start(const QString& filePath)
{
    LevelController& levelController = LevelController::getInstance();
    levelController.initializeLevels(filePath);

    mainWindow.setScene();
    mainWindow.updateConnections();
    mainWindow.show();
    playerController.moveRight();
}

void GameController::onZoomInEvent(){
    mainWindow.zoomIn();
}

void GameController::onZoomOutEvent(){
    mainWindow.zoomOut();
}
