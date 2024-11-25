#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <world.h>

class PlayerController : public QObject
{
    Q_OBJECT

public:
    PlayerController();
    void moveUp(std::unique_ptr<Protagonist>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width, int height);
    void moveDown(std::unique_ptr<Protagonist>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width, int height);
    void moveLeft(std::unique_ptr<Protagonist>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width, int height);
    void moveRight(std::unique_ptr<Protagonist>& protagonist, std::vector<std::unique_ptr<Tile>>& tiles, int width, int height);

};

#endif // PLAYERCONTROLLER_H
