#include "moverightcommand.h"
#include "Controller/enemycontroller.h"
#include "Controller/playercontroller.h"

MoveRightCommand::MoveRightCommand() {}
/**
 * @brief MoveRightCommand::execute movement command results in either an enemy attack, or movement to given direction
 */
void MoveRightCommand::execute() {

    playerController.updatePlayerDirection(Player::Right);

    if (!enemyController.checkForEnemy(EnemyController::Position::Right)) {
        playerController.moveRight();
        playerController.checkForHealthPack();
        if (playerController.checkForPrevLevel() || playerController.checkForNextLevel()){
            playerController.moveRight();
        }
    }
    else{
        playerController.checkForPoison();
    }



}
