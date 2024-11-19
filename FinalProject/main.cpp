#include "mainwindow.h"
#include "world.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    World world;
    world.createWorld(":/world_images/maze1.png", 10, 10, 0.25f);

    return a.exec();
}
