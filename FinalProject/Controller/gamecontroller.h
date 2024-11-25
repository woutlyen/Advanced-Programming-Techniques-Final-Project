#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Controller/inputcontroller.h"
#include "mainwindow.h"
#include "world.h"

class GameController
{
public:
    GameController();
    void start();

private:
    MainWindow mainWindow;
    std::vector<std::unique_ptr<Tile>> tiles;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Tile>> healthPacks;
    std::unique_ptr<Protagonist> protagonist;

    InputController inputController;
};

#endif // GAMECONTROLLER_H
