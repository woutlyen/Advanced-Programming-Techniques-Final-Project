#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <world.h>

class PlayerController : public QObject
{
    Q_OBJECT

public:
    void moveUp() const;
    void moveDown() const;
    void moveLeft() const;
    void moveRight() const;
    void checkForHealthPack() const;
    bool checkForPrevLevel() const;
    bool checkForNextLevel() const;
};

#endif // PLAYERCONTROLLER_H
