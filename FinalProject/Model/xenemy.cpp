#include "xenemy.h"

XEnemy::XEnemy(int xPosition, int yPosition, float strength)
: EnemyWrapper(xPosition, yPosition, strength)
{
    setXPos(xPosition);
    setYPos(yPosition);
    setValue(strength);
    qDebug() << "XEnemy intialized!";
}

void XEnemy::attack()
{
    qDebug() << "XEnemy attacks!";
}
