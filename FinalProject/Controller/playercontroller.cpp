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
<<<<<<< HEAD
            useEnergy(protagonist, val);
            protagonist->setYPos(protagonist->getYPos()-1);
=======
            level.protagonist->setEnergy(level.protagonist->getEnergy() - val);
            level.protagonist->setYPos(level.protagonist->getYPos()-1);
>>>>>>> main
        }
    }
}

void PlayerController::moveDown() const{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();

    if (level.protagonist->getYPos() < level.height-1 && level.protagonist->getEnergy() >= 1){
        float val = (level.tiles.at((level.protagonist->getYPos()+1) * level.width + level.protagonist->getXPos())->getValue());
        if (val != std::numeric_limits<float>::infinity()){
<<<<<<< HEAD
            useEnergy(protagonist, val);
            protagonist->setYPos(protagonist->getYPos()+1);
=======
            level.protagonist->setEnergy(level.protagonist->getEnergy() - val);
            level.protagonist->setYPos(level.protagonist->getYPos()+1);
>>>>>>> main
        }
    }
}

void PlayerController::moveLeft() const{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();

    if (level.protagonist->getXPos() > 0 && level.protagonist->getEnergy() >= 1){
        float val = (level.tiles.at(level.protagonist->getYPos() * level.width + level.protagonist->getXPos() -1)->getValue());
        if (val != std::numeric_limits<float>::infinity()){
<<<<<<< HEAD
            useEnergy(protagonist, val);
            protagonist->setXPos(protagonist->getXPos()-1);
=======
            level.protagonist->setEnergy(level.protagonist->getEnergy() - val);
            level.protagonist->setXPos(level.protagonist->getXPos()-1);
>>>>>>> main
        }
    }
}

void PlayerController::moveRight() const{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();

    if (level.protagonist->getXPos() < level.width-1 && level.protagonist->getEnergy() >= 1){
        float val = (level.tiles.at(level.protagonist->getYPos() * level.width + level.protagonist->getXPos() +1)->getValue());
        if (val != std::numeric_limits<float>::infinity()){
<<<<<<< HEAD
            useEnergy(protagonist, val);
            protagonist->setXPos(protagonist->getXPos()+1);
=======
            level.protagonist->setEnergy(level.protagonist->getEnergy() - val);
            level.protagonist->setXPos(level.protagonist->getXPos()+1);
>>>>>>> main
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
<<<<<<< HEAD
            heal(protagonist, 100.0f);
            addEnergy(protagonist, 25.0f);
=======
            level.protagonist->setHealth(100.0f);
            level.protagonist->setEnergy(100.0f);
>>>>>>> main
            healthPack->setValue(0.0f);
            break;
        }
    }
}

<<<<<<< HEAD
void PlayerController::takeDamage(std::unique_ptr<Player>& protagonist, float damage)
{
    protagonist->setHealth(std::max(0.0f, protagonist->getHealth() - damage));
}

void PlayerController::heal(std::unique_ptr<Player> &protagonist, float hp)
{
    protagonist->setHealth(std::min(100.0f, protagonist->getHealth() + hp));
}

void PlayerController::useEnergy(std::unique_ptr<Player> &protagonist, float energy)
{
    protagonist->setEnergy(std::max(0.0f, protagonist->getEnergy() - energy));
}

void PlayerController::addEnergy(std::unique_ptr<Player> &protagonist, float energy)
{
    protagonist->setEnergy(std::min(100.0f, protagonist->getEnergy() + energy));
}

void PlayerController::updatePlayerDirection(std::unique_ptr<Player>& protagonist, Player::Direction dir){
    protagonist->setDirection(dir);
}

void PlayerController::poisoned(std::unique_ptr<Player>& protagonist,float poisonLevel)
{
    protagonist->setPoisoned();
    takeDamage(protagonist, poisonLevel);
}

void PlayerController::checkForPoison(std::unique_ptr<Player> &protagonist, std::vector<std::unique_ptr<Tile> > &poisonedTiles)
{
    int X = protagonist->getXPos();
    int Y = protagonist->getYPos();

    for(auto& poisonedTile : poisonedTiles){
        if(poisonedTile->getXPos() == X && poisonedTile->getYPos() == Y && poisonedTile->getValue() != 0){
            poisoned(protagonist, poisonedTile->getValue());
            break;
        }
    }
}
=======
<<<<<<< HEAD
void PlayerController::updatePlayerDirection(std::unique_ptr<Player>& protagonist, Player::Direction dir){
    protagonist->setDirection(dir);
}
=======
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

>>>>>>> 17a849c5978e350734172370ba409f84affe3958
>>>>>>> main
