#ifndef COMMAND_H
#define COMMAND_H

#include "Controller/enemycontroller.h"
#include "Controller/playercontroller.h"
class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
protected:
    EnemyController enemyController;
    PlayerController playerController;
};

#endif // COMMAND_H
