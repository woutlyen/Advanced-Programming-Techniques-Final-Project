#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Controller/inputcontroller.h"
#include "Controller/playercontroller.h"
#include "mainwindow.h"
#include "world.h"

#include <QObject>

class GameController : public QObject
{
    Q_OBJECT

public:
    GameController(QObject *parent = nullptr);
    void start();

private:
    MainWindow mainWindow;
    std::vector<std::unique_ptr<Tile>> tiles;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Tile>> healthPacks;
    std::unique_ptr<Protagonist> protagonist;

    PlayerController playerController;
    InputController inputController;

private slots:
    void onUpPressed();
    void onDownPressed();
    void onLeftPressed();
    void onRightPressed();
};

#endif // GAMECONTROLLER_H
