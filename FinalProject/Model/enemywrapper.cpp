#include "enemywrapper.h"

EnemyWrapper::EnemyWrapper(std::unique_ptr<Enemy> enemy): wrappedEnemy(std::move(enemy)) {}

EnemyWrapper::EnemyWrapper(int xPosition, int yPosition, float strength): wrappedEnemy(std::make_unique<Enemy>(xPosition, yPosition, strength)){}

void EnemyWrapper::attack()
{
    if(!wrappedEnemy->getDefeated()){
        qDebug() << "Enemy attacks!";
        wrappedEnemy->setDefeated(true);
    }
}
