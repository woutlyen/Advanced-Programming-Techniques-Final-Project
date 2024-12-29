#include "moverightcommand.h"
#include "Controller/enemycontroller.h"
#include "Controller/playercontroller.h"

MoveRightCommand::MoveRightCommand() {}

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
        playerController.startFight();
        playerController.checkForPoison();
    }



}
