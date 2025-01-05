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
    void start(const QString& filePath);

    // Static method to get the singleton instance
    static GameController& getInstance();

    // Delete copy constructor and assignment operator
    GameController(const GameController&) = delete;
    GameController& operator=(const GameController&) = delete;

    // Pathfinding functions
    void goTo(int x, int y);
    void goToNearestEnemy();
    void goToNearestHealthpack();

private:
    GameController(QObject *parent = nullptr);

    MainWindow mainWindow;

    PlayerController playerController;
    EnemyController enemyController;
    InputController inputController;
    PathfinderController pathfinderController;

    // Autoplay related member variables
    bool isAutoplay{false};
    bool onPath{false};
    std::vector<int> path;
    int pathIndex{0};
    bool isAutoplayRunning{false};
    bool movingToEnemy{false};
    QTimer* autoplayTimer = new QTimer(this);
    bool attackFailed{false};

    // Autoplay related functions
    void sendMoveCommand(int move);
    bool isTileWalkable(int x, int y) const;
    std::vector<int> convertPath(std::vector<int> path);
    void disableAutoplay();
    bool checkInsufficientStats() const;
    void pathSetUp();

  private slots:
    void onZoomInEvent();
    void onZoomOutEvent();
    void onAutoPlay();
    void autoplay();
    void move();

};


#endif // GAMECONTROLLER_H
