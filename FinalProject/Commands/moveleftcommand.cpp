#include "moveleftcommand.h"
#include "Controller/enemycontroller.h"
#include "Controller/playercontroller.h"

MoveLeftCommand::MoveLeftCommand() {}

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
        playerController.startFight();
        playerController.checkForPoison();
    }



}
