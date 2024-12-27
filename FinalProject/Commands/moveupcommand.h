#ifndef MOVEUPCOMMAND_H
#define MOVEUPCOMMAND_H

#include "Controller/enemycontroller.h"
#include "Controller/playercontroller.h"
#include "command.h"
#include "qobject.h"
#include "qtmetamacros.h"

class MoveUpCommand : public Command {
public:
    MoveUpCommand();
    void execute() override;
};

#endif // MOVEUPCOMMAND_H
