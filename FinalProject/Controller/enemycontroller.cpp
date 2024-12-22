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
                if(enemy->getXPos() == X && enemy->getYPos() == Y-1 && !enemy->getDefeated()){
                    attack(enemy, protagonist);
                    return true;
                }
            }
        }
        return false;
    case(Down):
        if (Y < height-1){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X && enemy->getYPos() == Y+1 && !enemy->getDefeated()){
                    attack(enemy, protagonist);
                    return true;
                }
            }
        }
        return false;
    case(Left):
        if (X > 0){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X-1 && enemy->getYPos() == Y && !enemy->getDefeated()){
                    attack(enemy, protagonist);
                    return true;
                }
            }
        }
        return false;
    case(Right):
        if (X < width -1){
            for(auto& enemy : enemies){
                if(enemy->getXPos() == X+1 && enemy->getYPos() == Y && !enemy->getDefeated()){
                    attack(enemy, protagonist);
                    return true;
                }
            }
        }
        return false;
    };



}

void EnemyController::attack(std::unique_ptr<Enemy> &enemy, std::unique_ptr<Player> &protagonist)
{
    qDebug() << "Enemy attacks!";
    protagonist->setHealth(protagonist->getHealth()-enemy->getValue());
    enemy->setDefeated(true);
}

