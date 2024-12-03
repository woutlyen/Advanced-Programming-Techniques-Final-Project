#include "playercontroller.h"

PlayerController::PlayerController() {}

void PlayerController::moveUp(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width){
    if (protagonist->getYPos() > 0 && protagonist->getEnergy() >= 1){
        protagonist->setEnergy(protagonist->getEnergy()
                               - (tiles.at((protagonist->getYPos()-1)*width+protagonist->getXPos())->getValue()));
        protagonist->setYPos(protagonist->getYPos()-1);
    }
}

void PlayerController::moveDown(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width, int height){
    if (protagonist->getYPos() < height-1 && protagonist->getEnergy() >= 1){
        protagonist->setEnergy(protagonist->getEnergy()
                               - (tiles.at((protagonist->getYPos()+1)*width+protagonist->getXPos())->getValue()));
        protagonist->setYPos(protagonist->getYPos()+1);
    }
}

void PlayerController::moveLeft(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width){
    if (protagonist->getXPos() > 0 && protagonist->getEnergy() >= 1){
        protagonist->setEnergy(protagonist->getEnergy()
                               - (tiles.at(protagonist->getYPos()*width+protagonist->getXPos()-1)->getValue()));
        protagonist->setXPos(protagonist->getXPos()-1);
    }
}

void PlayerController::moveRight(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width){
    if (protagonist->getXPos() < width-1 && protagonist->getEnergy() >= 1){
        protagonist->setEnergy(protagonist->getEnergy()
                               - (tiles.at(protagonist->getYPos()*width+protagonist->getXPos()+1)->getValue()));
        protagonist->setXPos(protagonist->getXPos()+1);

    }
}
