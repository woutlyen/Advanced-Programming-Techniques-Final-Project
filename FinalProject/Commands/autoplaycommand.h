#ifndef AUTOPLAYCOMMAND_H
#define AUTOPLAYCOMMAND_H

#include "command.h"

class AutoPlayCommand : public Command
{
public:
    AutoPlayCommand();
    void execute() override;
};

#endif // AUTOPLAYCOMMAND_H
