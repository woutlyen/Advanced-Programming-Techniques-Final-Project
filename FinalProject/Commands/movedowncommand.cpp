#include "movedowncommand.h"
#include "Controller/enemycontroller.h"
#include "Controller/playercontroller.h"

MoveDownCommand::MoveDownCommand() {}

/**
 * @brief MoveDownCommand::execute movement command results in either an enemy attack, or movement to given direction
 */
void MoveDownCommand::execute() {
    playerController.updatePlayerDirection(Player::Front);

    if (!enemyController.checkForEnemy(EnemyController::Position::Down)) {
        playerController.moveDown();
        playerController.checkForHealthPack();
        if (playerController.checkForPrevLevel() || playerController.checkForNextLevel()){
            playerController.moveDown();
        }
    }
    else{
        playerController.checkForPoison();
    }
}
