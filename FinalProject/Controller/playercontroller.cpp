#include "playercontroller.h"
#include "Controller/levelcontroller.h"
#include "mainwindow.h"

#include <QApplication>

void PlayerController::moveUp() const{
    auto& level = getCurrentLevel();
    auto& protagonist = level.protagonist;


    if (protagonist->getYPos() > 0 && protagonist->getEnergy() >= 1 && protagonist->getHealth() >= 1){
        float val = (level.tiles.at((protagonist->getYPos()-1) * level.width + protagonist->getXPos())->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            protagonist->setEnergy(protagonist->getEnergy() - (1.0 - val) - 0.1);
            protagonist->setYPos(protagonist->getYPos()-1);
        }
    }
}

void PlayerController::moveDown() const{
    auto& level = getCurrentLevel();
    auto& protagonist = level.protagonist;

    if (protagonist->getYPos() < level.height-1 && protagonist->getEnergy() >= 1 && protagonist->getHealth() >= 1){
        float val = (level.tiles.at((protagonist->getYPos()+1) * level.width + protagonist->getXPos())->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            protagonist->setEnergy(protagonist->getEnergy() - (1.0 - val) - 0.1);
            protagonist->setYPos(protagonist->getYPos()+1);
        }
    }
}

void PlayerController::moveLeft() const{
    auto& level = getCurrentLevel();
    auto& protagonist = level.protagonist;

    if (protagonist->getXPos() > 0 && protagonist->getEnergy() >= 1 && protagonist->getHealth() >= 1){
        float val = (level.tiles.at(protagonist->getYPos() * level.width + protagonist->getXPos() -1)->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            protagonist->setEnergy(protagonist->getEnergy() - (1.0 - val) - 0.1);
            protagonist->setXPos(protagonist->getXPos()-1);
        }
    }
}

void PlayerController::moveRight() const{
    auto& level = getCurrentLevel();
    auto& protagonist = level.protagonist;

    if (protagonist->getXPos() < level.width-1 && protagonist->getEnergy() >= 1 && protagonist->getHealth() >= 1){
        float val = (level.tiles.at(protagonist->getYPos() * level.width + protagonist->getXPos() +1)->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            protagonist->setEnergy(protagonist->getEnergy() - (1.0 - val) - 0.1);
            protagonist->setXPos(protagonist->getXPos()+1);
        }
    }
}

void PlayerController::checkForHealthPack() const
{
    auto& protagonist = getCurrentLevel().protagonist;

    int X = protagonist->getXPos();
    int Y = protagonist->getYPos();

    for(auto& healthPack : getCurrentLevel().healthPacks){
        if(healthPack->getXPos() == X && healthPack->getYPos() == Y && healthPack->getValue() != 0){
            protagonist->setHealth(100.0f);
            protagonist->setEnergy(100.0f);
            healthPack->setValue(0.0f);
            break;
        }
    }
}

void PlayerController::updatePlayerDirection(Player::Direction dir){
    getCurrentLevel().protagonist->setDirection(dir);
}

bool PlayerController::checkForPoison()
{
    auto& protagonist = getCurrentLevel().protagonist;
    int X = protagonist->getXPos();
    int Y = protagonist->getYPos();

    // As long as thare are poisonTiles, keep checking for poison every second
    if(!getCurrentLevel().poisonedTiles.empty()){
        QTimer::singleShot(1000, this, &PlayerController::checkForPoison);
    }

    for(const auto& poisonedTile : getCurrentLevel().poisonedTiles){
        if(poisonedTile->getXPos() == X && poisonedTile->getYPos() == Y && poisonedTile->getValue() != 0){
            protagonist->setPoisoned(true);
            protagonist->takeDamage(poisonedTile->getValue());
            return true;
        }
    }

    return false;
}

bool PlayerController::checkForPrevLevel() const
{
    auto& level = getCurrentLevel();
    auto& protagonist = level.protagonist;
    LevelController& levelController = LevelController::getInstance();
    MainWindow * mainWindow = static_cast<MainWindow*>(QApplication::activeWindow());

    if(protagonist->getXPos() == level.prev_level_x_pos && protagonist->getYPos() == level.prev_level_y_pos){
        levelController.setCurrentLevelNr(levelController.getCurrentLevelNr() -1);
        mainWindow->setScene();
        mainWindow->updateConnections();
        return true;
    }
    return false;
}

bool PlayerController::checkForNextLevel() const
{
    auto& level = getCurrentLevel();
    auto& protagonist = level.protagonist;
    LevelController& levelController = LevelController::getInstance();
    MainWindow * mainWindow = static_cast<MainWindow*>(QApplication::activeWindow());

    if(protagonist->getXPos() == level.next_level_x_pos && protagonist->getYPos() == level.next_level_y_pos){
        levelController.setCurrentLevelNr(levelController.getCurrentLevelNr() +1);
        mainWindow->setScene();
        mainWindow->updateConnections();
        return true;
    }
    return false;
}

