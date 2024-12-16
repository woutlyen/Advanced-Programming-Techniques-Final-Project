#include <QApplication>

#include <Controller/gamecontroller.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QString filePath = ":/levels.xml";
    //QString filePath = ":/levels_test.xml";

    GameController gameController;
    gameController.start(filePath);

    return a.exec();
}
