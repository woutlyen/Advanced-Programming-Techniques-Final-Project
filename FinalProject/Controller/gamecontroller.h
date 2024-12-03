#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Controller/enemycontroller.h"
#include "Controller/inputcontroller.h"
#include "Controller/playercontroller.h"
#include "Model/player.h"
#include "mainwindow.h"
#include "world.h"

#include <QGraphicsScene>
#include <QObject>

class GameController : public QObject
{
    Q_OBJECT

public:
    GameController(QObject *parent = nullptr);
    void start();

private:
    MainWindow mainWindow;
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    std::vector<std::vector<std::unique_ptr<Enemy>>> enemies;
    std::vector<std::vector<std::unique_ptr<Tile>>> healthPacks;
    std::vector<std::unique_ptr<Player>> protagonist;
    std::vector<int> width;
    std::vector<int> heigth;

    std::vector<QGraphicsScene*> scenes2D;
    std::vector<QGraphicsScene*> scenesText;
    std::size_t currentLevel {0};

    PlayerController playerController;
    EnemyController enemyController;
    InputController inputController;

private slots:
    void onUpPressed();
    void onDownPressed();
    void onLeftPressed();
    void onRightPressed();
    void onHomePressed();
    void onEndPressed();
    void onZoomEvent(double zoomFactor);
};

#endif // GAMECONTROLLER_H
