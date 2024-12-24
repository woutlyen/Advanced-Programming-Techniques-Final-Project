#include "movedowncommand.h"
#include "Controller/enemycontroller.h"
#include "Controller/playercontroller.h"

MoveDownCommand::MoveDownCommand() {}

void MoveDownCommand::execute() {
    EnemyController enemyController;
    PlayerController playerController;

    playerController.updatePlayerDirection(Player::Front);
    if (!enemyController.checkForEnemy(EnemyController::Position::Down)) {
        playerController.moveDown();
        playerController.checkForHealthPack();
        if (playerController.checkForPrevLevel() || playerController.checkForNextLevel()){
            playerController.moveDown();
        }
    }
}
