#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Controller/enemycontroller.h"
#include "Controller/inputcontroller.h"
#include "Controller/playercontroller.h"
#include "mainwindow.h"

#include <QGraphicsScene>
#include <QObject>
#include <functional>


class GameController : public QObject {
    Q_OBJECT

  public:
    GameController(QObject *parent = nullptr);
    void start(QString& filePath);

  private:

    MainWindow mainWindow;

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
    bool checkForPrevLevel();
    bool checkForNextLevel();
    void parseLevels(QString& filePath);
    void generateLevel(int levelNumber);


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
