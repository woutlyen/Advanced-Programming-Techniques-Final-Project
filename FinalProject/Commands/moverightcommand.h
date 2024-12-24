#ifndef MOVERIGHTCOMMAND_H
#define MOVERIGHTCOMMAND_H

#include "command.h"

class MoveRightCommand : public Command
{
public:
    MoveRightCommand();
    void execute() override;
};

#endif // MOVERIGHTCOMMAND_H
