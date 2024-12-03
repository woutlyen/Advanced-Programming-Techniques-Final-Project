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

    void zoom(double zoomFactor);

  private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
