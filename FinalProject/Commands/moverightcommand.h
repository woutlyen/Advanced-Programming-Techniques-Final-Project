#ifndef MOVERIGHTCOMMAND_H
#define MOVERIGHTCOMMAND_H

#include "Controller/enemycontroller.h"
#include "Controller/playercontroller.h"
#include "command.h"
#include "qobject.h"
#include "qtmetamacros.h"

class MoveRightCommand : public Command {

public:
    MoveRightCommand();
    void execute() override;
};

#endif // MOVERIGHTCOMMAND_H
