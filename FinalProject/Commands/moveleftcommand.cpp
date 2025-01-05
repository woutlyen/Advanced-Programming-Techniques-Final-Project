#include "moveleftcommand.h"
#include "Controller/enemycontroller.h"
#include "Controller/playercontroller.h"

MoveLeftCommand::MoveLeftCommand() {}

/**
 * @brief MoveLeftCommand::execute movement command results in either an enemy attack, or movement to given direction
 */
void MoveLeftCommand::execute() {

    playerController.updatePlayerDirection(Player::Left);

    if (!enemyController.checkForEnemy(EnemyController::Position::Left)) {
        playerController.moveLeft();
        playerController.checkForHealthPack();
        if (playerController.checkForPrevLevel() || playerController.checkForNextLevel()){
            playerController.moveLeft();
        }
    }
    else{
        playerController.checkForPoison();
    }



}
