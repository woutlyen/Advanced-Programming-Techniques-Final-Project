#include "moveupcommand.h"
#include "Controller/enemycontroller.h"
#include "Controller/playercontroller.h"
#include <QTimer>

MoveUpCommand::MoveUpCommand() {}

/**
 * @brief MoveUpCommand::execute movement command results in either an enemy attack, or movement to given direction
 */
void MoveUpCommand::execute() {

    playerController.updatePlayerDirection(Player::Back);

    if (!enemyController.checkForEnemy(EnemyController::Position::Up)){
        playerController.moveUp();
        playerController.checkForHealthPack();
        if (playerController.checkForPrevLevel() || playerController.checkForNextLevel()){
            playerController.moveUp();
        }
    }
    else{
        playerController.checkForPoison();
    }


}
