#include "enemycontroller.h"

/**
 * @brief EnemyController::checkForEnemy checks whether an enemy is present at the tile the player
 * wants to move at. If present, check whether the player attacks. If the player attacks, enemy attacks back.
 * @param pos
 * @return true if enemy found at position
 */
bool EnemyController::checkForEnemy(const Position pos)
{
    auto& level = getCurrentLevel();
    auto& enemies = level.enemies;
    auto& player = level.protagonist;

    int X = player->getXPos();
    int Y = player->getYPos();

    switch(pos){
    case(Up):
        if (Y > 0){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X && enemy->getYPos() == Y-1 && !enemy->getDefeated()){
                    if(player->attack(enemy->getValue())){
                        checkPoison(enemy);
                        enemy->attack(player);
                    }
                    return true;
                }
            }
        }
        return false;
    case(Down):
        if (Y < level.height-1){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X && enemy->getYPos() == Y+1 && !enemy->getDefeated()){
                    if(player->attack(enemy->getValue())){
                        checkPoison(enemy);
                        enemy->attack(player);
                    }
                    return true;
                }
            }
        }
        return false;
    case(Left):
        if (X > 0){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X-1 && enemy->getYPos() == Y && !enemy->getDefeated()){
                    if(player->attack(enemy->getValue())){
                        checkPoison(enemy);
                        enemy->attack(player);
                    }
                    return true;
                }
            }
        }
        return false;
    case(Right):
        if (X < level.width -1){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X+1 && enemy->getYPos() == Y && !enemy->getDefeated()){
                    if(player->attack(enemy->getValue())){
                        checkPoison(enemy);
                        enemy->attack(player);
                    }
                    return true;
                }
            }
        }
        return false;
    };
    return false;
}

/**
 * @brief EnemyController::checkPoison signals to the LevelController to generate poisoned tiles after attack on a PEnemy type
 * @param enemy
 */
void EnemyController::checkPoison(const std::unique_ptr<EnemyWrapper> &enemy)
{
    if(PEnemyWrapper* penemy = dynamic_cast<PEnemyWrapper *>(enemy.get())){
        if(!penemy->getPoisonStarted()){
            LevelController::getInstance().setPEnemyConnection(penemy);
            LevelController::getInstance().generatePoisonedTiles(penemy->getXPos(), penemy->getYPos(), penemy->getPoisonLevel(), 1);
        }
    }
}

