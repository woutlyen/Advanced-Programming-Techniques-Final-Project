#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Model/player.h"
#include <QObject>
#include <world.h>

class PlayerController : public QObject
{
    Q_OBJECT

public:
    PlayerController();
    void moveUp(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width);
    void moveDown(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width, int height);
    void moveLeft(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width);
    void moveRight(std::unique_ptr<Player>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width);

    void updatePlayerDirection(std::unique_ptr<Player> &protagonist, Player::Direction dir);
};

#endif // PLAYERCONTROLLER_H
