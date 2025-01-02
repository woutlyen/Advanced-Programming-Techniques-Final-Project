#include "gotocommand.h"
#include "Controller/gamecontroller.h"

#include <iostream>

GotoCommand::GotoCommand(int x, int y) : targetX(x), targetY(y) {}

void GotoCommand::execute() {
    std::cout << "Protagonist is moving to position (" << targetX << ", " << targetY << ")." << std::endl;

    GameController::getInstance().goTo(targetX, targetY);
}
