#ifndef PENEMYWRAPPER_H
#define PENEMYWRAPPER_H

#include "enemywrapper.h"

/**
 * @brief The PEnemyWrapper class is a wrapper class for managing and interacting with a unique pointer to PEnemy,
 * while also extending it with new methods and fields. It inherits from EnemyWrapper.
 */
class PEnemyWrapper : public EnemyWrapper
{
    Q_OBJECT
public:
    PEnemyWrapper(std::unique_ptr<Enemy> &&enemy);
    ~PEnemyWrapper() override = default;

    // wrapper methods
    [[nodiscard]] float getPoisonLevel() const noexcept {return static_cast<PEnemy*>(wrappedEnemy.get())->getPoisonLevel();};
    void setPoisonLevel(float value) noexcept {static_cast<PEnemy*>(wrappedEnemy.get())->setPoisonLevel(value);};
    std::string serialize() noexcept override{return static_cast<PEnemy*>(wrappedEnemy.get())->serialize();};
    bool poison(){return static_cast<PEnemy*>(wrappedEnemy.get())->poison();};

    // own methods
    void attack(std::unique_ptr<Player> &player) override;

    bool getPoisonStarted() const;
    void setPoisonStarted(bool newPoisonStarted);


private:
    bool poisonStarted{false};
public slots:
    void poisonLevelUpdatedWrappedPenemy(int value){emit poisonLevelUpdated(value);};

signals:
    void poisonLevelUpdated(int value);
    void startPoison(int value);
};

#endif // PENEMYWRAPPER_H
