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
                if(enemy->getXPos() == X && enemy->getYPos() == Y-1 && !enemy->getDefeated()){
                    checkPoison(enemy);
                    enemy->attack(protagonist);
                    return true;
                }
            }
        }
        return false;
    case(Down):
        if (Y < level.height-1){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X && enemy->getYPos() == Y+1 && !enemy->getDefeated()){
                    checkPoison(enemy);
                    enemy->attack(protagonist);
                    return true;
                }
            }
        }
        return false;
    case(Left):
        if (X > 0){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X-1 && enemy->getYPos() == Y && !enemy->getDefeated()){
                    checkPoison(enemy);
                    enemy->attack(protagonist);
                    return true;
                }
            }
        }
        return false;
    case(Right):
        if (X < level.width -1){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X+1 && enemy->getYPos() == Y && !enemy->getDefeated()){
                    checkPoison(enemy);
                    enemy->attack(protagonist);
                    return true;
                }
            }
        }
        return false;
    };
}

void EnemyController::checkPoison(std::unique_ptr<EnemyWrapper> &enemy)
{
    if(PEnemyWrapper* penemy = dynamic_cast<PEnemyWrapper *>(enemy.get())){
        if(!penemy->getPoisonStarted()){
            LevelController::getInstance().setPEnemyConnection(penemy);
            LevelController::getInstance().generatePoisonedTiles(penemy->getXPos(), penemy->getYPos(), penemy->getPoisonLevel(), 1);
        }
    }
}

