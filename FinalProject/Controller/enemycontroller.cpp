#include "enemycontroller.h"
#include "Controller/levelcontroller.h"

EnemyController::EnemyController() {}

bool EnemyController::checkForEnemy(Position pos)
{
    LevelController& levelController = LevelController::getInstance();
    Level& level = levelController.getCurrentLevel();

    int X = level.protagonist->getXPos();
    int Y = level.protagonist->getYPos();

    switch(pos){
    case(Up):
        if (Y > 0){
            for(auto& enemy : level.enemies){
                if(enemy->getXPos() == X && enemy->getYPos() == Y-1){
                    level.protagonist->setHealth(level.protagonist->getHealth()-5.0f);
                    return true;
                }
            }
        }
        return false;
    case(Down):
        if (Y < level.height-1){
            for(auto& enemy : level.enemies){
                if(enemy->getXPos() == X && enemy->getYPos() == Y+1){
                    level.protagonist->setHealth(level.protagonist->getHealth()-5.0f);
                    return true;
                }
            }
        }
        return false;
    case(Left):
        if (X > 0){
            for(auto& enemy : level.enemies){
                if(enemy->getXPos() == X-1 && enemy->getYPos() == Y){
                    level.protagonist->setHealth(level.protagonist->getHealth()-5.0f);
                    return true;
                }
            }
        }
        return false;
    case(Right):
        if (X < level.width -1){
            for(auto& enemy : level.enemies){
                if(enemy->getXPos() == X+1 && enemy->getYPos() == Y){
                    level.protagonist->setHealth(level.protagonist->getHealth()-5.0f);
                    return true;
                }
            }
        }
        return false;
    };
}
