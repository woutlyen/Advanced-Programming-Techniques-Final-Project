#ifndef PLAYER_H
#define PLAYER_H
#include "world.h"

class Player : public Protagonist
{
public:
    Player();
    enum Direction {Front, Back, Left, Right};
    void setDirection(Direction dir);

private:
    Direction currentDirection;

signals:
    void directionChanged(Direction dir);
};

#endif // PLAYER_H
