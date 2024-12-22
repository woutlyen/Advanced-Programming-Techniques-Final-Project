#include "playercontroller.h"
#include "Controller/levelcontroller.h"

PlayerController::PlayerController() {}

void PlayerController::moveUp(){
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

void PlayerController::moveDown(){
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

void PlayerController::moveLeft(){
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

void PlayerController::moveRight(){
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

void PlayerController::checkForHealthPack()
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

