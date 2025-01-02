#include "attacknearestenemycommand.h"

#include <iostream>

#include <Controller/gamecontroller.h>

AttackNearestEnemyCommand::AttackNearestEnemyCommand() {}

void AttackNearestEnemyCommand::execute() {
    std::cout << "Protagonist attacks the nearest enemy." << std::endl;
    GameController::getInstance().goToNearestEnemy();
}
