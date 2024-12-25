#include "player.h"

Player::Player(): currentDirection{Front} {

}

void Player::setDirection(Direction dir)
{
    currentDirection = dir;
    emit directionChanged(currentDirection);
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
