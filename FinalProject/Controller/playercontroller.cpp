#include "playercontroller.h"

PlayerController::PlayerController() {}

void PlayerController::moveUp(std::unique_ptr<Protagonist>& protagonist){
    protagonist->setYPos(protagonist->getYPos()-1);
}

void PlayerController::moveDown(std::unique_ptr<Protagonist>& protagonist){
    protagonist->setYPos(protagonist->getYPos()+1);
}

void PlayerController::moveLeft(std::unique_ptr<Protagonist>& protagonist){
    protagonist->setXPos(protagonist->getXPos()-1);
}

void PlayerController::moveRight(std::unique_ptr<Protagonist>& protagonist){
    protagonist->setXPos(protagonist->getXPos()+1);
}
