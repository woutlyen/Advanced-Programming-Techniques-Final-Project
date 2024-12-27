#include "autoplaycommand.h"
#include <iostream>

AutoPlayCommand::AutoPlayCommand() {}

void AutoPlayCommand::execute() {
    std::cout << "Autoplay started" << std::endl;
}
