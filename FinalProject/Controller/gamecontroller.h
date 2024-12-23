#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Controller/enemycontroller.h"
#include "Controller/inputcontroller.h"
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

  private slots:
    void onZoomInEvent();
    void onZoomOutEvent();
};


#endif // GAMECONTROLLER_H
