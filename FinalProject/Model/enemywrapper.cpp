#include "enemywrapper.h"

EnemyWrapper::EnemyWrapper(std::unique_ptr<Enemy> enemy): wrappedEnemy(std::move(enemy)) {
    connect(wrappedEnemy.get(), &Enemy::dead, this, &EnemyWrapper::onWrappedEnemyDied);
}

EnemyWrapper::EnemyWrapper(int xPosition, int yPosition, float strength): wrappedEnemy(std::make_unique<Enemy>(xPosition, yPosition, strength)){
    connect(wrappedEnemy.get(), &Enemy::dead, this, &EnemyWrapper::onWrappedEnemyDied);
}

void EnemyWrapper::attack(std::unique_ptr<Player> &player)
{
    if(!getDefeated()){
        qDebug() << "Enemy attacks!";
        player->takeDamage(getValue());
        setDefeated(true);
    }
}
