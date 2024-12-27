#include "xenemy.h"

XEnemy::XEnemy(int xPosition, int yPosition, float strength)
: EnemyWrapper(xPosition, yPosition, strength)
{
    setXPos(xPosition);
    setYPos(yPosition);
    setValue(strength);
}

void XEnemy::attack(std::unique_ptr<Player> &player)
{
    qDebug() << "XEnemy attacks!";
    if(!transformed){
        setTransformed(true);
    }
    else{
        if(hitCount < 3){
            hitCount++;
            player->takeDamage(getValue());
        }
        else{
            setDefeated(true);
        }
    }
}

bool XEnemy::getTransformed() const
{
    return transformed;
}

void XEnemy::setTransformed(bool newTransformed)
{
    transformed = newTransformed;
    if(transformed){
        emit transform();
    }
}
