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
#include <functional>


class GameController : public QObject {
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

    std::vector<QGraphicsScene *> scenesText;
    std::vector<QGraphicsScene *> scenes2D;
    std::size_t currentLevel{0};

    PlayerController playerController;
    EnemyController enemyController;
    InputController inputController;

    enum ViewMode { Graphics2DView,
                    TextView };

    ViewMode currentMode{};

    // Where is the best place to define this typedef?
    /*typedef void (GameController::*gamecontroller_method_t)();*/
    //typedef std::function<void()> func;
    std::unordered_map<std::string, std::function<void()>> gamecontrollerMethodMap;
    bool checkForNewLevel();


  private slots:
    void moveProtagonistUp();
    void moveProtagonistDown();
    void moveProtagonistLeft();
    void moveProtagonistRight();
    void onHomePressed();
    void onEndPressed();
    void changeViewMode();
    void processCommand(QString textCommand);
    void onZoomInEvent();
    void onZoomOutEvent();
};


#endif // GAMECONTROLLER_H
