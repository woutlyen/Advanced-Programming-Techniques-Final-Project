#include "playercontroller.h"

PlayerController::PlayerController() {}

void PlayerController::moveUp(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width){
    if (protagonist->getYPos() > 0 && protagonist->getEnergy() >= 1){
        float val = (tiles.at((protagonist->getYPos()-1)*width+protagonist->getXPos())->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            useEnergy(protagonist, val);
            protagonist->setYPos(protagonist->getYPos()-1);
        }
    }
}

void PlayerController::moveDown(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width, int height){
    if (protagonist->getYPos() < height-1 && protagonist->getEnergy() >= 1){
        float val = (tiles.at((protagonist->getYPos()+1)*width+protagonist->getXPos())->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            useEnergy(protagonist, val);
            protagonist->setYPos(protagonist->getYPos()+1);
        }
    }
}

void PlayerController::moveLeft(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width){
    if (protagonist->getXPos() > 0 && protagonist->getEnergy() >= 1){
        float val = (tiles.at(protagonist->getYPos()*width+protagonist->getXPos()-1)->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            useEnergy(protagonist, val);
            protagonist->setXPos(protagonist->getXPos()-1);
        }
    }
}

void PlayerController::moveRight(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width){
    if (protagonist->getXPos() < width-1 && protagonist->getEnergy() >= 1){
        float val = (tiles.at(protagonist->getYPos()*width+protagonist->getXPos()+1)->getValue());
        if (val != std::numeric_limits<float>::infinity()){
            useEnergy(protagonist, val);
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
            heal(protagonist, 100.0f);
            addEnergy(protagonist, 25.0f);
            healthPack->setValue(0.0f);
            break;
        }
    }
}

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
