#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <world.h>

class PlayerController : public QObject
{
    Q_OBJECT

public:
    PlayerController();
    void takeDamage(std::unique_ptr<Player>& protagonist, float damage);
    void heal(std::unique_ptr<Player>& protagonist, float hp);
    void useEnergy(std::unique_ptr<Player>& protagonist, float energy);
    void addEnergy(std::unique_ptr<Player>& protagonist, float energy);
    void moveUp() const;
    void moveDown() const;
    void moveLeft() const;
    void moveRight() const;
    void checkForHealthPack() const;
    bool checkForPrevLevel() const;
    bool checkForNextLevel() const;
    void updatePlayerDirection(std::unique_ptr<Player> &protagonist, Player::Direction dir);
    void poisoned(std::unique_ptr<Player> &protagonist, float poisonLevel);
    void checkForPoison(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& poisonedTiles);
};

#endif // PLAYERCONTROLLER_H
