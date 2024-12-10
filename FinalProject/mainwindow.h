#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    void setScene(QGraphicsScene* scene);
    ~MainWindow();

  public slots:
    void zoomIn();
    void zoomOut();


  private:
    Ui::MainWindow *ui;
    const double zoomFactor {1.15};  // Factor to zoom in/out by
    int currentZoomLevel {0};     // Track zoom level (to prevent over-zooming)

};
#endif // MAINWINDOW_H
