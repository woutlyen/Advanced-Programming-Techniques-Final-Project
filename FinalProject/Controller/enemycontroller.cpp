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
