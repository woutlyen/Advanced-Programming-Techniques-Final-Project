#ifndef GOTOCOMMAND_H
#define GOTOCOMMAND_H

#include "command.h"

class GotoCommand : public Command
{
public:
    GotoCommand(int x, int y);
    void execute() override;

private:
    int targetX;
    int targetY;
};

#endif // GOTOCOMMAND_H
