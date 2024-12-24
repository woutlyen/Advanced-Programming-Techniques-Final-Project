#include "moveupcommand.h"
#include "Controller/enemycontroller.h"
#include "Controller/playercontroller.h"

MoveUpCommand::MoveUpCommand() {}

void MoveUpCommand::execute() {
    EnemyController enemyController;
    PlayerController playerController;

    playerController.updatePlayerDirection(Player::Back);
    if (!enemyController.checkForEnemy(EnemyController::Position::Up)){
        playerController.moveUp();
        playerController.checkForHealthPack();
        if (playerController.checkForPrevLevel() || playerController.checkForNextLevel()){
            playerController.moveUp();
        }
    }
}
