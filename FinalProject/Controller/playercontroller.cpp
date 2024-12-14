#include "playercontroller.h"

PlayerController::PlayerController() {}

void PlayerController::moveUp(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width){
    if (protagonist->getYPos() > 0 && protagonist->getEnergy() >= 1){
        float val = (tiles.at((protagonist->getYPos()-1)*width+protagonist->getXPos())->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            protagonist->setEnergy(protagonist->getEnergy() - val);
            protagonist->setYPos(protagonist->getYPos()-1);
        }
    }
}

void PlayerController::moveDown(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width, int height){
    if (protagonist->getYPos() < height-1 && protagonist->getEnergy() >= 1){
        float val = (tiles.at((protagonist->getYPos()+1)*width+protagonist->getXPos())->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            protagonist->setEnergy(protagonist->getEnergy() - val);
            protagonist->setYPos(protagonist->getYPos()+1);
        }
    }
}

void PlayerController::moveLeft(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width){
    if (protagonist->getXPos() > 0 && protagonist->getEnergy() >= 1){
        float val = (tiles.at(protagonist->getYPos()*width+protagonist->getXPos()-1)->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            protagonist->setEnergy(protagonist->getEnergy() - val);
            protagonist->setXPos(protagonist->getXPos()-1);
        }
    }
}

void PlayerController::moveRight(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width){
    if (protagonist->getXPos() < width-1 && protagonist->getEnergy() >= 1){
        float val = (tiles.at(protagonist->getYPos()*width+protagonist->getXPos()+1)->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            protagonist->setEnergy(protagonist->getEnergy() - val);
            protagonist->setXPos(protagonist->getXPos()+1);
        }
    }
}

void PlayerController::checkForHealthPack(std::unique_ptr<Player> &protagonist, std::vector<std::unique_ptr<Tile> > &healthPacks)
{
    int X = protagonist->getXPos();
    int Y = protagonist->getYPos();

    for(auto& healthPack : healthPacks){
        if(healthPack->getXPos() == X && healthPack->getYPos() == Y && healthPack->getValue() != 0){
            protagonist->setHealth(100.0f);
            protagonist->setEnergy(100.0f);
            healthPack->setValue(0.0f);
            break;
        }
    }
}

bool PlayerController::checkForNewLevel(std::unique_ptr<Player> &protagonist, std::vector<std::unique_ptr<Tile> > &tiles, int width)
{
    float val = (tiles.at(protagonist->getYPos()*width+protagonist->getXPos())->getValue());
    if (val == 1.0f){
        return true;
    }

    return false;
}

bool PlayerController::playerOnLeftOfMap(std::unique_ptr<Player> &protagonist, int width)
{
    if (protagonist->getXPos() < width/2){
        return true;
    }
    else{
        return false;
    }
}
