#include "helpcommand.h"

#include <iostream>

HelpCommand::HelpCommand() {}

void HelpCommand::execute() {
    std::cout << "Available commands: up, down, left, right, attack, take, goto x y, help" << std::endl;
}
