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


GameController& GameController::getInstance() {
    static GameController instance;
    return instance;
}

void GameController::start(const QString& filePath)
{
    LevelController& levelController = LevelController::getInstance();
    levelController.initializeLevels(filePath);

    mainWindow.setScene();
    mainWindow.updateConnections();
    mainWindow.show();
    inputController.executeCommand("right");
}

/**
 * @brief GameController::autoplay initialises the autoplay loop. Player tries to defeat all enemies,
 * while replenishing health and energy when these values are low.
 */
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
            if(checkInsufficientStats() || attackFailed){
                path = pathfinderController.findNearestHealthPack();

                if(path.empty()){
                    qDebug() << "No healthpacks left. Game Over!";
                    disableAutoplay();
                    return;
                }
                movingToEnemy = false;
                qDebug() << "Path to hp found " << path;
            }
            else{
                path = pathfinderController.findNearestEnemy();

                if(path.empty()){
                    qDebug() << "No enemies left. Yay!";
                    disableAutoplay();
                    return;
                }
                movingToEnemy = true;
                qDebug() << "Path to enemies found "  << path;
            }

            pathSetUp();

        }

        int beforeX = player->getXPos();
        int beforeY = player->getYPos();

        qDebug() << "On pathIndex " << pathIndex;
        sendMoveCommand(path[pathIndex]);

        if(movingToEnemy && checkInsufficientStats()){
            qDebug() << "Not enough hp/ energy";
            onPath = false;
            isAutoplayRunning = false;
            return;
        }

        if(player->getXPos() == beforeX && player->getYPos() == beforeY){ // no movement due to enemy in the way
            if(!player->isStrongEnough() || checkInsufficientStats()){
                qDebug() << "Not enough hp";
                attackFailed = true;
                onPath = false;
                isAutoplayRunning = false;
                return;
            }
            else{
                qDebug() << "repeating movement";
                path.insert(path.begin() + pathIndex + 1, path[pathIndex]);
            }
        }

        if(pathIndex < (int)path.size() - 1){
            pathIndex++;
        }
        else{
            attackFailed = false;
            onPath = false;
        }
    }
    isAutoplayRunning = false;

}

/**
 * @brief GameController::sendMoveCommand translates the given int to a movement command
 * @param move
 */
void GameController::sendMoveCommand(int move)
{
    /*
    *     7 0 1
    *     6   2
    *     5 4 3
    */

    qDebug() << "Move is " << move;

    switch (move) {
    case 0:
        inputController.executeCommand("up");
        break;
    case 2:
        inputController.executeCommand("right");
        break;
    case 4:
        inputController.executeCommand("down");
        break;
    case 6:
        inputController.executeCommand("left");
        break;
    }
}

/**
 * @brief GameController::isTileWalkable check whether a tile is walkable in pathfinding mode
 * @param x
 * @param y
 * @return true if the tile is not a wall, nor a portal to the next/previous level
 */
bool GameController::isTileWalkable(int x, int y) const
{
    if(LevelController::getInstance().getTileValue(x,y) != std::numeric_limits<float>::infinity() && !(x == LevelController::getInstance().getCurrentLevel().next_level_x_pos && y == LevelController::getInstance().getCurrentLevel().next_level_y_pos) && !(x == LevelController::getInstance().getCurrentLevel().prev_level_x_pos && y == LevelController::getInstance().getCurrentLevel().prev_level_y_pos)){
        return true;
    }
    return false;
}

/**
 * @brief GameController::convertPath converts diagonal movements returned from the pathfinder to "up, down, left, right" movements
 * @param path
 * @return converted path with only "up, down, left, right" movements
 */
std::vector<int> GameController::convertPath(std::vector<int> path)
{
    /*
    *     7 0 1
    *     6   2
    *     5 4 3
    */

    std::vector<int> convertedPath;
    int x = LevelController::getInstance().getCurrentLevel().protagonist->getXPos();
    int y = LevelController::getInstance().getCurrentLevel().protagonist->getYPos();

    for (size_t i = 0; i < path.size(); i++){
        switch (path[i]) {
        case 0:
            convertedPath.push_back(0);
            y--;
            break;
        case 1:
            if(isTileWalkable(x, y-1)){
                convertedPath.push_back(0); //add up movement
                convertedPath.push_back(2); //add right movement
            }
            else{
                convertedPath.push_back(2); //add right movement
                convertedPath.push_back(0); //add up movement
            }
            x++;
            y--;
            break;
        case 2:
            convertedPath.push_back(2);
            x++;
            break;
        case 3:
            if(isTileWalkable(x, y+1)){
                convertedPath.push_back(4); //add down movement
                convertedPath.push_back(2); //add right movement
            }
            else{
                convertedPath.push_back(2); //add right movement
                convertedPath.push_back(4); //add down movement
            }
            x++;
            y++;
            break;

        case 4:
            convertedPath.push_back(4); //add down movement
            y++;
            break;
        case 5:
            if(isTileWalkable(x, y+1)){
                convertedPath.push_back(4); //add down movement
                convertedPath.push_back(6);//add left movement
            }
            else{
                convertedPath.push_back(6);//add left movement
                convertedPath.push_back(4); //add down movement
            }
            x--;
            y++;
            break;
        case 6:
            convertedPath.push_back(6);//add left movement
            x--;
            break;
        case 7:
            if(isTileWalkable(x, y-1)){
                convertedPath.push_back(0); //add up movement
                convertedPath.push_back(6);//add left movement
            }
            else{
                convertedPath.push_back(6);//add left movement
                convertedPath.push_back(0); //add up movement
            }
            x--;
            y--;
            break;
        }
    }
    qDebug() << "path converted from " << path << " to " << convertedPath;
    return convertedPath;
}

void GameController::disableAutoplay()
{
    autoplayTimer->stop();
    isAutoplay = false;
    isAutoplayRunning = false;
    movingToEnemy = false;
    onPath = false;
    path.clear();
    LevelController::getInstance().clearAutoplayPath();
}

void GameController::goTo(int x, int y)
{
    if(!onPath){
        path.clear();

        auto & player = LevelController::getInstance().getCurrentLevel().protagonist;

        Tile playerPosition(player->getXPos(), player->getYPos(), 0.0f);
        Tile goToTile{x,y,0.0f};

        path = pathfinderController.calculatePath(playerPosition, goToTile);
        pathSetUp();
        move();
    }
    else{
        std::cout << "Player already moving to a target. Wait until player reaches destination." << std::endl;
    }

}

void GameController::goToNearestEnemy()
{
    if(!onPath){
        path.clear();

        auto & player = LevelController::getInstance().getCurrentLevel().protagonist;

        Tile playerPosition(player->getXPos(), player->getYPos(), 0.0f);

        path = pathfinderController.findNearestEnemy();
        pathSetUp();
        move();
    }
    else{
        std::cout << "Player already moving to a target. Wait until player reaches destination." << std::endl;
    }
}

void GameController::goToNearestHealthpack()
{
    if(!onPath){
        path.clear();

        auto & player = LevelController::getInstance().getCurrentLevel().protagonist;

        Tile playerPosition(player->getXPos(), player->getYPos(), 0.0f);

        path = pathfinderController.findNearestHealthPack();
        pathSetUp();
        move();
    }
    else{
        std::cout << "Player already moving to a target. Wait until player reaches destination." << std::endl;
    }
}

/**
 * @brief GameController::move for the specific pathfinding commands that are not part of the autoplay
 */
void GameController::move()
{
    auto& player = LevelController::getInstance().getCurrentLevel().protagonist;

    int beforeX = player->getXPos();
    int beforeY = player->getYPos();

    qDebug() << "On pathIndex " << pathIndex;
    sendMoveCommand(path[pathIndex]);

    if(player->getXPos() == beforeX && player->getYPos() == beforeY){ // no movement due to enemy in the way
            qDebug() << "repeating movement";
            path.insert(path.begin() + pathIndex + 1, path[pathIndex]);
    }

    if(pathIndex < (int)path.size() - 1){
        pathIndex++;
        QTimer::singleShot(500, this, &GameController::move);
    }
    else{
        std::cout << "Destination reached!" << std::endl;
        onPath = false;
    }
}

bool GameController::checkInsufficientStats() const
{
    const auto & player = LevelController::getInstance().getCurrentLevel().protagonist;

    if(player->getEnergy() < 25 || player->getHealth() < 25){
        return true;
    }
    return false;
}

void GameController::pathSetUp()
{
    if(!path.empty()){
        path = convertPath(path);
        pathIndex = 0;
        onPath = true;
        LevelController::getInstance().showAutoplayPath(path);
    }
}

void GameController::onZoomInEvent(){
    mainWindow.zoomIn();
}

void GameController::onZoomOutEvent(){
    mainWindow.zoomOut();
}

void GameController::onAutoPlay()
{
    path.clear();

    if(!isAutoplay){
        isAutoplay = true;
        autoplayTimer->start(500);
        isAutoplayRunning = false;
        autoplay();
    }
    else{
        disableAutoplay();
    }

}
