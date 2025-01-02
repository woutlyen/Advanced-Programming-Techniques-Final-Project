#include "takenearesthealthpackcommand.h"

#include <iostream>

#include <Controller/gamecontroller.h>

TakeNearestHealthPackCommand::TakeNearestHealthPackCommand() {}

void TakeNearestHealthPackCommand::execute() {
    std::cout << "Protagonist takes the nearest health pack." << std::endl;
    GameController::getInstance().goToNearestHealthpack();
}
