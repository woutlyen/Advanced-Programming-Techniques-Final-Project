#include "enemycontroller.h"

bool EnemyController::checkForEnemy(const Position pos)
{
    auto& level = getCurrentLevel();
    auto& enemies = level.enemies;
    auto& protagonist = level.protagonist;

    int X = protagonist->getXPos();
    int Y = protagonist->getYPos();

    switch(pos){
    case(Up):
        if (Y > 0){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X && enemy->getYPos() == Y-1){
                    enemy->attack(protagonist);
                    return true;
                }
            }
        }
        return false;
    case(Down):
        if (Y < level.height-1){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X && enemy->getYPos() == Y+1){
                    enemy->attack(protagonist);
                    return true;
                }
            }
        }
        return false;
    case(Left):
        if (X > 0){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X-1 && enemy->getYPos() == Y){
                    enemy->attack(protagonist);
                    return true;
                }
            }
        }
        return false;
    case(Right):
        if (X < level.width -1){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X+1 && enemy->getYPos() == Y){
                    enemy->attack(protagonist);
                    return true;
                }
            }
        }
        return false;
    };
}

