#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Controller/enemycontroller.h"
#include "Controller/inputcontroller.h"
#include "Controller/playercontroller.h"
#include "Model/player.h"
#include "mainwindow.h"
#include "world.h"
#include "View/worldview2d.h"
#include "View/worldviewtext.h"
#include "Model/worldrevised.h"

#include <QGraphicsScene>
#include <QObject>
#include <functional>


class GameController : public QObject {
    Q_OBJECT

  public:
    GameController(QObject *parent = nullptr);
    void start(QString& filePath);

  private:
    struct Level {
        int number;
        int xpos;
        int ypos;
        int healthpacks;
        int enemies;
        float pratio;
        float xratio;
        QString visual_map;
        QString data_map;
        int grid_size;
        int visual_grid_size;
    };

    WorldRevised world;
    WorldViewText worldViewText;
    WorldView2D worldView2D;

    MainWindow mainWindow;
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    std::vector<std::vector<std::unique_ptr<Enemy>>> enemies;
    std::vector<std::vector<std::unique_ptr<Tile>>> healthPacks;
    std::vector<std::unique_ptr<Player>> protagonist;
    std::vector<int> width;
    std::vector<int> height;
    std::size_t gridSize{64};
    QList<Level> levels;

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
