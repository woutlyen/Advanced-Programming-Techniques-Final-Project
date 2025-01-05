#ifndef ENEMYWRAPPER_H
#define ENEMYWRAPPER_H
#include "Model/player.h"
#include "world.h"
#include <QDebug>

/**
 * @brief The EnemyWrapper class is a wrapper class for managing and interacting with a unique pointer to Enemy,
 * while also extending it with new methods and fields
 */
class EnemyWrapper: public QObject
{
    Q_OBJECT
public:
    EnemyWrapper(std::unique_ptr<Enemy> &&enemy);
    EnemyWrapper(int xPosition, int yPosition, float strength);
    virtual ~EnemyWrapper() = default;

    // wrapper methods
    bool getDefeated() const noexcept {return wrappedEnemy->getDefeated();}
    void setDefeated(bool value) noexcept {wrappedEnemy->setDefeated(value);}
    virtual std::string serialize() noexcept {return wrappedEnemy->serialize();}
    void setXPos(int newPos) noexcept {wrappedEnemy->setXPos(newPos);};
    void setYPos(int newPos) noexcept {wrappedEnemy->setYPos(newPos);};
    [[nodiscard]] int getXPos() const noexcept {return wrappedEnemy->getXPos();};
    [[nodiscard]] int getYPos() const noexcept {return wrappedEnemy->getYPos();};
    [[nodiscard]] float getValue() const noexcept {return wrappedEnemy->getValue();} ;
    void setValue(float newValue) noexcept {wrappedEnemy->setValue(newValue);};

    // new methods
    virtual void attack(std::unique_ptr<Player> &player);

protected:
    std::unique_ptr<Enemy> wrappedEnemy;

protected slots:
    void onWrappedEnemyDied(){emit dead();};

signals:
    void dead();
};

#endif // ENEMYWRAPPER_H
