#include "player.h"

Player::Player(): currentDirection{Front} {

}

void Player::setDirection(Direction dir)
{
    currentDirection = dir;
    emit directionChanged(currentDirection);
}
