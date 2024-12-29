 #include "gamecontroller.h"
#include "Controller/levelcontroller.h"

GameController::GameController(QObject *parent) : QObject(parent) {
    // Install the InputController as an event filter
    qApp->installEventFilter(&inputController);

    // Connect InputController signals to GameController slots
    connect(&inputController, &InputController::zoomIn, this, &GameController::onZoomInEvent);
    connect(&inputController, &InputController::zoomOut, this, &GameController::onZoomOutEvent);
    connect(&inputController, &InputController::autoplay, this, &GameController::onAutoPlay);


    connect(autoplayTimer, &QTimer::timeout, this, &GameController::autoplay);

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

void GameController::autoplay()
{
    auto & level = LevelController::getInstance().getCurrentLevel();
    auto & player = level.protagonist;

    if(isAutoplay && player->getAlive()){

        if (isAutoplayRunning) {
            return;
        }

        isAutoplayRunning = true;

        if(!onPath){
            pathIndex = 0;
            if(player->getEnergy() < 25 || player->getHealth() < 25){
                path = pathfinderController.findNearestHealthPack();

                if(path.empty()){
                    qDebug() << "No healthpacks left. Game Over!";
                    player->setEnergy(0);
                    isAutoplay = false;
                    isAutoplayRunning = false;
                    return;
                }
                movingToEnemy = false;
                qDebug() << "Path to hp found " << path;
            }
            else{
                path = pathfinderController.findNearestEnemy();

                if(path.empty()){
                    qDebug() << "No enemies left. Yay!";
                    isAutoplay = false;
                    isAutoplayRunning = false;
                    return;
                }
                qDebug() << "Path to enemies found "  << path;
                movingToEnemy = true;
            }

            onPath = true;
        }

        int beforeX = player->getXPos();
        int beforeY = player->getYPos();

        qDebug() << "On pathIndex " << pathIndex;
        sendMoveCommand(path[pathIndex]);

        if(movingToEnemy && (player->getEnergy() < 25 || player->getHealth() < 25)){
            qDebug() << "Not enough hp/ energy";
            onPath = false;
            isAutoplayRunning = false;
            return;
        }

        if(player->getXPos() == beforeX && player->getYPos() == beforeY){ // no movement due to enemy in the way
            qDebug() << "repeating movement";
            path.insert(path.begin() + pathIndex + 1, path[pathIndex]);
        }

        if(pathIndex < (int)path.size() - 1){
            pathIndex++;
        }
        else{
            onPath = false;
        }

    }
    isAutoplayRunning = false;

}

void GameController::sendMoveCommand(int move)
{
    /*
    *     7 0 1
    *     6   2
    *     5 4 3
    */

    auto & player = LevelController::getInstance().getCurrentLevel().protagonist;
    qDebug() << "Move is " << move;

    switch (move) {
    case 0:
        inputController.executeCommand("up");
        break;
    case 1:
        if(isTileWalkable(player->getXPos(), player->getYPos()-1)){
            inputController.executeCommand("up");
            path[pathIndex] = 0; // correcting to actual path movement
            path.insert(path.begin() + pathIndex + 1, 2); //add right movement
        }
        else{
            inputController.executeCommand("right");
            path[pathIndex] = 2; // correcting to actual path movement
            path.insert(path.begin() + pathIndex + 1, 0); //add up movement
        }
        break;
    case 2:
        inputController.executeCommand("right");
        break;
    case 3:
        if(isTileWalkable(player->getXPos(), player->getYPos()+1)){
            inputController.executeCommand("down");
            path[pathIndex] = 4; // correcting to actual path movement
            path.insert(path.begin() + pathIndex + 1, 2); //add right movement
        }
        else{
            inputController.executeCommand("right");
            path[pathIndex] = 2; // correcting to actual path movement
            path.insert(path.begin() + pathIndex + 1, 4); //add down movement
        }
        break;
    case 4:
        inputController.executeCommand("down");
        break;
    case 5:
        if(isTileWalkable(player->getXPos(), player->getYPos()+1)){
            inputController.executeCommand("down");
            path[pathIndex] = 4; // correcting to actual path movement
            path.insert(path.begin() + pathIndex + 1, 6); //add left movement
        }
        else{
            inputController.executeCommand("left");
            path[pathIndex] = 6; // correcting to actual path movement
            path.insert(path.begin() + pathIndex + 1, 4); //add down movement
        }
        break;
    case 6:
        inputController.executeCommand("left");
        break;
    case 7:
        if(isTileWalkable(player->getXPos(), player->getYPos()-1)){
            inputController.executeCommand("up");
            path[pathIndex] = 0; // correcting to actual path movement
            path.insert(path.begin() + pathIndex + 1, 6); //add left movement
        }
        else{
            inputController.executeCommand("left");
            path[pathIndex] = 6; // correcting to actual path movement
            path.insert(path.begin() + pathIndex + 1, 0); //add up movement
        }
        break;
    }
}

bool GameController::isTileWalkable(int x, int y)
{
    if(LevelController::getInstance().getTileValue(x,y) != std::numeric_limits<float>::infinity() && !(x == LevelController::getInstance().getCurrentLevel().next_level_x_pos && y == LevelController::getInstance().getCurrentLevel().next_level_y_pos) && !(x == LevelController::getInstance().getCurrentLevel().prev_level_x_pos && y == LevelController::getInstance().getCurrentLevel().prev_level_y_pos)){
        return true;
    }
    return false;
}

void GameController::onZoomInEvent(){
    mainWindow.zoomIn();
}

void GameController::onZoomOutEvent(){
    mainWindow.zoomOut();
}

void GameController::onAutoPlay()
{
    if(!isAutoplay){
        isAutoplay = true;
        autoplayTimer->start(500);
        isAutoplayRunning = false;
        autoplay();
    }
    else{
        autoplayTimer->stop();
        isAutoplay = false;
    }

}
