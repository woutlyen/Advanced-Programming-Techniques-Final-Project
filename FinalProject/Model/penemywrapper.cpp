#include "penemywrapper.h"

PEnemyWrapper::PEnemyWrapper(std::unique_ptr<Enemy> enemy): EnemyWrapper(std::move(enemy)){
    std::unique_ptr<PEnemy> wrappedPEnemy = std::unique_ptr<PEnemy>(static_cast<PEnemy*>(wrappedEnemy.release()));
    connect(wrappedPEnemy.get(), &PEnemy::poisonLevelUpdated, this, &PEnemyWrapper::poisonLevelUpdatedWrappedPenemy);
    wrappedEnemy = std::move(wrappedPEnemy);
}

void PEnemyWrapper::attack(std::unique_ptr<Player> &player)
{
    if(!getDefeated() && !getPoisonStarted()){
        qDebug() << "PEnemy attacks!";
        player->takeDamage(getValue());
        player->setPoisoned();
        setPoisonStarted(true);
        emit startPoison(getPoisonLevel());
        poison();
    }
}

bool PEnemyWrapper::getPoisonStarted() const
{
    return poisonStarted;
}

void PEnemyWrapper::setPoisonStarted(bool newPoisonStarted)
{
    poisonStarted = newPoisonStarted;
}
