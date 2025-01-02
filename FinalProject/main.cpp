#include <QApplication>

#include <Controller/gamecontroller.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QString filePath = ":/levels.xml";
    //QString filePath = ":/levels_test.xml";

    GameController::getInstance().start(filePath);

    return a.exec();
}
