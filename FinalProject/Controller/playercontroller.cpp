#include "playercontroller.h"
#include "Controller/levelcontroller.h"
#include "mainwindow.h"

#include <QApplication>

void PlayerController::moveUp() const{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();

    if (level.protagonist->getYPos() > 0 && level.protagonist->getEnergy() >= 1){
        float val = (level.tiles.at((level.protagonist->getYPos()-1) * level.width + level.protagonist->getXPos())->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            level.protagonist->setEnergy(level.protagonist->getEnergy() - val);
            level.protagonist->setYPos(level.protagonist->getYPos()-1);
        }
    }
}

void PlayerController::moveDown() const{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();

    if (level.protagonist->getYPos() < level.height-1 && level.protagonist->getEnergy() >= 1){
        float val = (level.tiles.at((level.protagonist->getYPos()+1) * level.width + level.protagonist->getXPos())->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            level.protagonist->setEnergy(level.protagonist->getEnergy() - val);
            level.protagonist->setYPos(level.protagonist->getYPos()+1);
        }
    }
}

void PlayerController::moveLeft() const{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();

    if (level.protagonist->getXPos() > 0 && level.protagonist->getEnergy() >= 1){
        float val = (level.tiles.at(level.protagonist->getYPos() * level.width + level.protagonist->getXPos() -1)->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            level.protagonist->setEnergy(level.protagonist->getEnergy() - val);
            level.protagonist->setXPos(level.protagonist->getXPos()-1);
        }
    }
}

void PlayerController::moveRight() const{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();

    if (level.protagonist->getXPos() < level.width-1 && level.protagonist->getEnergy() >= 1){
        float val = (level.tiles.at(level.protagonist->getYPos() * level.width + level.protagonist->getXPos() +1)->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            level.protagonist->setEnergy(level.protagonist->getEnergy() - val);
            level.protagonist->setXPos(level.protagonist->getXPos()+1);
        }
    }
}

void PlayerController::checkForHealthPack() const
{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();

    int X = level.protagonist->getXPos();
    int Y = level.protagonist->getYPos();

    for(auto& healthPack : level.healthPacks){
        if(healthPack->getXPos() == X && healthPack->getYPos() == Y && healthPack->getValue() != 0){
            level.protagonist->setHealth(100.0f);
            level.protagonist->setEnergy(100.0f);
            healthPack->setValue(0.0f);
            break;
        }
    }
}

void PlayerController::takeDamage(float damage)
{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();
    level.protagonist->setHealth(std::max(0.0f, level.protagonist->getHealth() - damage));
}

void PlayerController::heal(float hp)
{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();
    level.protagonist->setHealth(std::min(100.0f, level.protagonist->getHealth() + hp));
}

void PlayerController::useEnergy(float energy)
{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();
    level.protagonist->setEnergy(std::max(0.0f, level.protagonist->getEnergy() - energy));
}

void PlayerController::addEnergy(float energy)
{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();
    level.protagonist->setEnergy(std::min(100.0f, level.protagonist->getEnergy() + energy));
}

void PlayerController::updatePlayerDirection(Player::Direction dir){
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();
    level.protagonist->setDirection(dir);
}

void PlayerController::poisoned(float poisonLevel)
{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();
    level.protagonist->setPoisoned();
    takeDamage(poisonLevel);
}

void PlayerController::checkForPoison(std::vector<std::unique_ptr<Tile> > &poisonedTiles)
{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();
    int X = level.protagonist->getXPos();
    int Y = level.protagonist->getYPos();

    for(auto& poisonedTile : poisonedTiles){
        if(poisonedTile->getXPos() == X && poisonedTile->getYPos() == Y && poisonedTile->getValue() != 0){
            poisoned(poisonedTile->getValue());
            break;
        }
    }
}

bool PlayerController::checkForPrevLevel() const
{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();

    MainWindow * mainWindow = static_cast<MainWindow*>(QApplication::activeWindow());

    if(level.protagonist->getXPos() == level.prev_level_x_pos && level.protagonist->getYPos() == level.prev_level_y_pos){
        levelController.setCurrentLevelNr(levelController.getCurrentLevelNr() -1);
        mainWindow->setScene();
        mainWindow->updateConnections();
        return true;
    }
    return false;
}

bool PlayerController::checkForNextLevel() const
{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();

    MainWindow * mainWindow = static_cast<MainWindow*>(QApplication::activeWindow());

    if(level.protagonist->getXPos() == level.next_level_x_pos && level.protagonist->getYPos() == level.next_level_y_pos){
        levelController.setCurrentLevelNr(levelController.getCurrentLevelNr() +1);
        mainWindow->setScene();
        mainWindow->updateConnections();
        return true;
    }
    return false;
}

