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
    bool getPoisoned(){return isPoisoned;};
    void takeDamage(float damage);
    void heal(float hp);
    void useEnergy(float energy);
    void addEnergy(float energy);

private:
    Direction currentDirection;
    bool isPoisoned {false};

signals:
    void directionChanged(Direction dir);
    void poisoned();
};

#endif // PLAYER_H
