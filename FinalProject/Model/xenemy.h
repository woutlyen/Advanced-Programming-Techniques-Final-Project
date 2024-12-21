#ifndef XENEMY_H
#define XENEMY_H

#include <world.h>

class XEnemy: public Enemy
{
public:
    XEnemy(int xPosition, int yPosition, float strength);
};

#endif // XENEMY_H
