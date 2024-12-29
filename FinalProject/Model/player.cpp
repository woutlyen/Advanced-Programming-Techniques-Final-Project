#include "player.h"
#include "qdebug.h"
#include "qtimer.h"

Player::Player(std::unique_ptr<Protagonist> protagonist): wrappedPlayer(std::move(protagonist)), currentDirection{Front} {
    connect(wrappedPlayer.get(), &Protagonist::energyChanged, this, &Player::energyChangedWrapped);
    connect(wrappedPlayer.get(), &Protagonist::healthChanged, this, &Player::healthChangedWrapped);
    connect(wrappedPlayer.get(), &Protagonist::posChanged, this, &Player::posChangedWrapped);
}

void Player::setDirection(Direction dir)
{
    currentDirection = dir;
    emit directionChanged(currentDirection);
}

void Player::setPoisoned(bool value)
{
    if(value){
        emit poisoned();
    }
}

void Player::takeDamage(float damage)
{
    setHealth(std::max(0.0f, getHealth() - damage));
}

void Player::heal(float hp)
{
    setHealth(std::min(100.0f, getHealth() + hp));
}

void Player::useEnergy(float energy)
{
    setEnergy(std::max(0.0f, getEnergy() - energy));
}

void Player::addEnergy(float energy)
{
    setEnergy(std::min(100.0f, getEnergy() + energy));
}

bool Player::getAlive() const
{
    return alive;
}

void Player::setAlive(bool newAlive)
{
    alive = newAlive;
}

