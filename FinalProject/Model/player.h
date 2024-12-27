#ifndef PLAYER_H
#define PLAYER_H
#include "world.h"

class Player : public Protagonist
{
    Q_OBJECT
public:
    Player();
    enum Direction {Front, Back, Left, Right};
    void setDirection(Direction dir);
    void setPoisoned(bool value);
    bool getPoisoned(){return isPoisoned;};
    void takeDamage(float damage);
    void heal(float hp);
    void useEnergy(float energy);
    void addEnergy(float energy);
    void initialize();

private:
    Direction currentDirection{Front};
    bool isPoisoned {false};
    QTimer* poisonTimer;
    int poisonDurationRemaining;


signals:
    void directionChanged(Direction dir);
    void poisoned();
    void poisonedOver();

private slots:
     void poisonDamage();
};

#endif // PLAYER_H
