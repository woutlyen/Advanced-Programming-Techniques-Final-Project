#ifndef MOVEDOWNCOMMAND_H
#define MOVEDOWNCOMMAND_H

#include "command.h"

class MoveDownCommand : public Command
{
public:
    MoveDownCommand();
    void execute() override;
};

#endif // MOVEDOWNCOMMAND_H
