#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H

#include "command.h"

class HelpCommand : public Command
{
public:
    HelpCommand();
    void execute() override;
};

#endif // HELPCOMMAND_H
