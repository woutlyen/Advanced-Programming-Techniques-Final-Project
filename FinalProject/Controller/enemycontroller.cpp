#include "enemycontroller.h"

EnemyController::EnemyController() {}

bool EnemyController::checkForEnemy(std::vector<std::unique_ptr<Enemy> > &enemies, std::unique_ptr<Player> &protagonist, int width, int height, Position pos)
{
    int X = protagonist->getXPos();
    int Y = protagonist->getYPos();

    switch(pos){
    case(Up):
        if (Y > 0){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X && enemy->getYPos() == Y-1){
                    protagonist->setHealth(protagonist->getHealth()-5.0f);
                    return true;
                }
            }
        }
        return false;
    case(Down):
        if (Y < height-1){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X && enemy->getYPos() == Y+1){
                    protagonist->setHealth(protagonist->getHealth()-5.0f);
                    return true;
                }
            }
        }
        return false;
    case(Left):
        if (X > 0){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X-1 && enemy->getYPos() == Y){
                    protagonist->setHealth(protagonist->getHealth()-5.0f);
                    return true;
                }
            }
        }
        return false;
    case(Right):
        if (X < width -1){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X+1 && enemy->getYPos() == Y){
                    protagonist->setHealth(protagonist->getHealth()-5.0f);
                    return true;
                }
            }
        }
        return false;
    };


}
