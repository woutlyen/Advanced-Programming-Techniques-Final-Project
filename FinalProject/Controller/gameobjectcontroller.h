#ifndef GAMEOBJECTCONTROLLER_H
#define GAMEOBJECTCONTROLLER_H

#include "Level.h"
#include "Controller/levelcontroller.h"
#include <QObject>

class GameObjectController: public QObject
{
    Q_OBJECT
public:

    GameObjectController() = default;

protected:
    Level& getCurrentLevel() const{return LevelController::getInstance().getCurrentLevel();};
};

#endif // GAMEOBJECTCONTROLLER_H
