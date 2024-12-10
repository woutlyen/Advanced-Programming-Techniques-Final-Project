#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //this->setCentralWidget(ui->graphicsView);
}

void MainWindow::setScene(QGraphicsScene *scene)
{
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::zoomIn()
{
    if (currentZoomLevel < 10) { // Limit maximum zoom in
        ui->graphicsView->scale(zoomFactor, zoomFactor);
        ++currentZoomLevel;
    }
}

void MainWindow::zoomOut()
{
    if (currentZoomLevel > -10) { // Limit maximum zoom out
        ui->graphicsView->scale(1/zoomFactor, 1/zoomFactor);
        --currentZoomLevel;
    }
}





