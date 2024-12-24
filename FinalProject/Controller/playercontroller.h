#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Model/player.h"
#include <QObject>
#include <world.h>

class PlayerController : public QObject
{
    Q_OBJECT

public:
    void takeDamage(float damage);
    void heal(float hp);
    void useEnergy(float energy);
    void addEnergy(float energy);
    void moveUp() const;
    void moveDown() const;
    void moveLeft() const;
    void moveRight() const;
    void checkForHealthPack() const;
    bool checkForPrevLevel() const;
    bool checkForNextLevel() const;
    void updatePlayerDirection(Player::Direction dir);
    void poisoned(float poisonLevel);
    void checkForPoison(std::vector<std::unique_ptr<Tile>>& poisonedTiles);
};

#endif // PLAYERCONTROLLER_H
