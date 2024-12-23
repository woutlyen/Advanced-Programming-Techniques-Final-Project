#ifndef TAKENEARESTHEALTHPACKCOMMAND_H
#define TAKENEARESTHEALTHPACKCOMMAND_H

#include "command.h"

class TakeNearestHealthPackCommand : public Command
{
public:
    TakeNearestHealthPackCommand();
    void execute() override;
};

#endif // TAKENEARESTHEALTHPACKCOMMAND_H
