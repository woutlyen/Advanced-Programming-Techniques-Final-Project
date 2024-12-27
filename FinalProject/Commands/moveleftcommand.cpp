#include "moveleftcommand.h"
#include "Controller/enemycontroller.h"
#include "Controller/playercontroller.h"

MoveLeftCommand::MoveLeftCommand() {}

void MoveLeftCommand::execute() {
    EnemyController enemyController;
    PlayerController playerController;

    playerController.updatePlayerDirection(Player::Left);
    if (!enemyController.checkForEnemy(EnemyController::Position::Left)) {
        playerController.moveLeft();
        playerController.checkForHealthPack();
        playerController.checkForPoison();
        if (playerController.checkForPrevLevel() || playerController.checkForNextLevel()){
            playerController.moveLeft();
        }
    }
}
