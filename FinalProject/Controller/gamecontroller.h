#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Controller/enemycontroller.h"
#include "Controller/inputcontroller.h"
#include "Controller/pathfindercontroller.h"
#include "Controller/playercontroller.h"
#include "mainwindow.h"

#include <QGraphicsScene>
#include <QObject>


class GameController : public QObject {
    Q_OBJECT

  public:
    GameController(QObject *parent = nullptr);
    void start(const QString& filePath);

  private:

    MainWindow mainWindow;

    PlayerController playerController;
    EnemyController enemyController;
    InputController inputController;
    PathfinderController pathfinderController;

    bool isAutoplay{false};
    bool onPath{false};
    std::vector<int> path;
    int pathIndex{0};
    void sendMoveCommand(int move);
    bool isTileWalkable(int x, int y);
    std::vector<int> convertPath(std::vector<int> path);
    bool isAutoplayRunning{false};
    bool movingToEnemy{false};

    QTimer* autoplayTimer = new QTimer(this);

  private slots:
    void onZoomInEvent();
    void onZoomOutEvent();
    void onAutoPlay();
    void autoplay();

};


#endif // GAMECONTROLLER_H
