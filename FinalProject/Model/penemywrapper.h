#ifndef PENEMYWRAPPER_H
#define PENEMYWRAPPER_H

#include "enemywrapper.h"

class PEnemyWrapper : public EnemyWrapper
{
public:
    PEnemyWrapper(std::unique_ptr<Enemy> enemy);
    ~PEnemyWrapper() override = default;

    void attack() override;
    [[nodiscard]] float getPoisonLevel() const noexcept {return static_cast<PEnemy*>(wrappedEnemy.get())->getPoisonLevel();};
    void setPoisonLevel(float value) noexcept {static_cast<PEnemy*>(wrappedEnemy.get())->setPoisonLevel(value);};
    std::string serialize() noexcept override{return static_cast<PEnemy*>(wrappedEnemy.get())->serialize();};
    bool poison(){return static_cast<PEnemy*>(wrappedEnemy.get())->poison();};

public slots:
    void poisonLevelUpdatedWrappedPenemy(int value){emit poisonLevelUpdated(value);};

signals:
    void poisonLevelUpdated(int value);
};

#endif // PENEMYWRAPPER_H
