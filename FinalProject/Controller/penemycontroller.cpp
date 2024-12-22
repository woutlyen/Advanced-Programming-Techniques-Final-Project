#include "penemycontroller.h"

PEnemyController::PEnemyController():EnemyController() {}

void PEnemyController::attack(std::unique_ptr<Enemy> &enemy, std::unique_ptr<Player> &protagonist)
{
    qDebug() << "PEnemy attacks!";
    if(PEnemy* penemy = dynamic_cast<PEnemy *>(enemy.get())){
        penemy->poison();
    }
}
