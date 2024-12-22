#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <world.h>

class PlayerController : public QObject
{
    Q_OBJECT

public:
    PlayerController();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void checkForHealthPack();

};

#endif // PLAYERCONTROLLER_H
