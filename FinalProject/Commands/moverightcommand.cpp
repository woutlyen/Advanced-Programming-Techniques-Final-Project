#include "moverightcommand.h"
#include "Controller/enemycontroller.h"
#include "Controller/playercontroller.h"

MoveRightCommand::MoveRightCommand() {}

void MoveRightCommand::execute() {
    EnemyController enemyController;
    PlayerController playerController;

    playerController.updatePlayerDirection(Player::Right);
    if (!enemyController.checkForEnemy(EnemyController::Position::Right)) {
        playerController.moveRight();
        playerController.checkForHealthPack();
        if (playerController.checkForPrevLevel() || playerController.checkForNextLevel()){
            playerController.moveRight();
        }
    }
}
