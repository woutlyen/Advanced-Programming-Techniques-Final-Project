#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->setCentralWidget(ui->graphicsView);
}

void MainWindow::setScene(QGraphicsScene *scene)
{
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::zoom(double zoomFactor) {
    ui->graphicsView->scale(zoomFactor, zoomFactor);
}
