#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>

#include <Model/player.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    void setScene();
    void setScale(double sx, double sy);
    void updateConnections();
    ~MainWindow();

    Ui::MainWindow *ui;

  public slots:
    void zoomIn();
    void zoomOut();


private slots:
    void updateEnergyBar(int value);
    void updateHealthBar(int value);
private:
    const double zoomFactor {1.15};  // Factor to zoom in/out by
    int currentZoomLevel {0};     // Track zoom level (to prevent over-zooming)

};
#endif // MAINWINDOW_H
