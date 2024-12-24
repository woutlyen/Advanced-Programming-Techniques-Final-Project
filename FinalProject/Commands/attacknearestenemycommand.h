#ifndef ATTACKNEARESTENEMYCOMMAND_H
#define ATTACKNEARESTENEMYCOMMAND_H

#include "command.h"

class AttackNearestEnemyCommand : public Command
{
public:
    AttackNearestEnemyCommand();
    void execute() override;
};

#endif // ATTACKNEARESTENEMYCOMMAND_H
