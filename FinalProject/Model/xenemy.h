#ifndef XENEMY_H
#define XENEMY_H

#include "Model/enemywrapper.h"
#include <world.h>

class XEnemy: public EnemyWrapper
{
    Q_OBJECT
public:
    XEnemy(int xPosition, int yPosition, float strength);

    bool getTransformed() const;
    void setTransformed(bool newTransformed);

private:
    void attack(std::unique_ptr<Player> &player) override;
    bool transformed{false};

    int hitCount = 0;
signals:
    void transform();
};

#endif // XENEMY_H
