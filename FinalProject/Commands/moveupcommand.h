#ifndef MOVEUPCOMMAND_H
#define MOVEUPCOMMAND_H

#include "command.h"

class MoveUpCommand : public Command
{
public:
    MoveUpCommand();
    void execute() override;
};

#endif // MOVEUPCOMMAND_H
