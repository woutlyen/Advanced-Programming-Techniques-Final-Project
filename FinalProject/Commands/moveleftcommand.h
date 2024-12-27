#ifndef MOVELEFTCOMMAND_H
#define MOVELEFTCOMMAND_H

#include "command.h"
#include "qobject.h"
#include "qtmetamacros.h"

class MoveLeftCommand : public Command
{
public:
    MoveLeftCommand();
    void execute() override;
};

#endif // MOVELEFTCOMMAND_H
