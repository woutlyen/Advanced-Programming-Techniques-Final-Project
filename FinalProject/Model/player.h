#ifndef PLAYER_H
#define PLAYER_H
#include "world.h"

class Player : public QObject
{
    Q_OBJECT
public:
    Player(std::unique_ptr<Protagonist> protagonist);
    enum Direction {Front, Back, Left, Right};
    void setDirection(Direction dir);
    void setPoisoned(bool value);
    void takeDamage(float damage);
    void heal(float hp);
    void useEnergy(float energy);
    void addEnergy(float energy);
    void attack(){emit playerAttack();};

    void setXPos(int newPos) noexcept {wrappedPlayer->setXPos(newPos);}
    void setYPos(int newPos) noexcept {wrappedPlayer->setYPos(newPos);}
    void setPos(int newX, int newY) noexcept {wrappedPlayer->setPos(newX, newY);}
    [[nodiscard]] float getHealth() const noexcept {return wrappedPlayer->getHealth();};
    void setHealth(float value) noexcept {wrappedPlayer->setHealth(value);}

    [[nodiscard]] float getEnergy() const noexcept {return wrappedPlayer->getEnergy();}
    void setEnergy(float value) noexcept {wrappedPlayer->setEnergy(value); if(value < 1){setAlive(false);}}
    [[nodiscard]] std::string serialize() noexcept{return wrappedPlayer->serialize();};

    [[nodiscard]] float getValue() const noexcept {return wrappedPlayer->getValue();} ;
    void setValue(float newValue) noexcept {wrappedPlayer->setValue(newValue);};
    [[nodiscard]] int getXPos() const noexcept {return wrappedPlayer->getXPos();};
    [[nodiscard]] int getYPos() const noexcept {return wrappedPlayer->getYPos();};

    bool getAlive() const;
    void setAlive(bool newAlive);

private:
    Direction currentDirection;
    std::unique_ptr<Protagonist> wrappedPlayer;

    bool alive{true};



signals:

    void posChanged(int x, int y);
    void healthChanged(int h);
    void energyChanged(int e);

    void directionChanged(Direction dir);
    void poisoned();

    void playerAttack();

private slots:
    void posChangedWrapped(int x, int y){emit posChanged(x,y);};
    void healthChangedWrapped(int h){emit healthChanged(h);};
    void energyChangedWrapped(int e){emit energyChanged(e);};
};

#endif // PLAYER_H
