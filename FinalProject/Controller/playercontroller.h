#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <world.h>

class PlayerController : public QObject
{
    Q_OBJECT

public:
    PlayerController();
    void moveUp(std::unique_ptr<Protagonist>& protagonist);
    void moveDown(std::unique_ptr<Protagonist>& protagonist);
    void moveLeft(std::unique_ptr<Protagonist>& protagonist);
    void moveRight(std::unique_ptr<Protagonist>& protagonist);

};

#endif // PLAYERCONTROLLER_H
