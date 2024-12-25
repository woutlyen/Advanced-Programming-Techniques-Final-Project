#include "penemywrapper.h"

PEnemyWrapper::PEnemyWrapper(std::unique_ptr<Enemy> enemy): EnemyWrapper(std::move(enemy)){
    std::unique_ptr<PEnemy> wrappedPEnemy = std::unique_ptr<PEnemy>(static_cast<PEnemy*>(wrappedEnemy.release()));
    wrappedEnemy = std::move(wrappedPEnemy);
}

void PEnemyWrapper::attack(std::unique_ptr<Player> &player)
{
    if(!getDefeated()){
        qDebug() << "PEnemy attacks!";
        poison();
    }
}
