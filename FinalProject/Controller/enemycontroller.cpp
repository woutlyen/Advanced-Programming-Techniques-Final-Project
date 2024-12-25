#include "enemycontroller.h"

bool EnemyController::checkForEnemy(const Position pos)
{
    auto& level = getCurrentLevel();
    auto& enemies = level.enemies;

    int X = level.protagonist->getXPos();
    int Y = level.protagonist->getYPos();

    switch(pos){
    case(Up):
        if (Y > 0){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X && enemy->getYPos() == Y-1){
                    attack(enemy);
                    return true;
                }
            }
        }
        return false;
    case(Down):
        if (Y < level.height-1){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X && enemy->getYPos() == Y+1){
                    attack(enemy);
                    return true;
                }
            }
        }
        return false;
    case(Left):
        if (X > 0){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X-1 && enemy->getYPos() == Y){
                    attack(enemy);
                    return true;
                }
            }
        }
        return false;
    case(Right):
        if (X < level.width -1){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X+1 && enemy->getYPos() == Y){
                    attack(enemy);
                    return true;
                }
            }
        }
        return false;
    };
}

