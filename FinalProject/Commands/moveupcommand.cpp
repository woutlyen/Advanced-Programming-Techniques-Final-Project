#include "moveupcommand.h"
#include "Controller/enemycontroller.h"
#include "Controller/playercontroller.h"
#include <QTimer>

MoveUpCommand::MoveUpCommand() {}

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
        playerController.startFight();
        playerController.checkForPoison();
    }


}
