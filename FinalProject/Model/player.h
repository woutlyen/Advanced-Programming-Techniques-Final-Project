#ifndef PLAYER_H
#define PLAYER_H
#include "world.h"

class Player : public Protagonist
{
    Q_OBJECT
public:
    Player();
    enum Direction {Front, Back, Left, Right};
    void setDirection(Direction dir);
    void setPoisoned(){emit poisoned(), isPoisoned=true;};
    bool isPoisoned {false};
    void takeDamage(float damage);
    void heal(float hp);
    void useEnergy(float energy);
    void addEnergy(float energy);

private:
    Direction currentDirection;

signals:
    void directionChanged(Direction dir);
    void poisoned();
};

#endif // PLAYER_H
