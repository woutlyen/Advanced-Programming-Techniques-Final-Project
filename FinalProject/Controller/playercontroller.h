#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Controller/gameobjectcontroller.h"
#include "Model/player.h"
#include "qtimer.h"
#include <world.h>

class PlayerController : public GameObjectController
{

public:
    void moveUp() const;
    void moveDown() const;
    void moveLeft() const;
    void moveRight() const;
    void checkForHealthPack() const;
    bool checkForPrevLevel() const;
    bool checkForNextLevel() const;
    void updatePlayerDirection(Player::Direction dir);
    void checkForPoison();

private:
    QTimer* poisonTimer = new QTimer(this);
    int poisonDurationRemaining = 3;
};

#endif // PLAYERCONTROLLER_H
