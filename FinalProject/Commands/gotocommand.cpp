#include "gotocommand.h"

#include <iostream>

GotoCommand::GotoCommand(int x, int y) : targetX(x), targetY(y) {}

void GotoCommand::execute() {
    std::cout << "TODO : Protagonist is moving to position (" << targetX << ", " << targetY << ")." << std::endl;
}
