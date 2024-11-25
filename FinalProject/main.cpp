#include <QApplication>

#include <Controller/gamecontroller.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    GameController gameController;
    gameController.start();

    return a.exec();
}
