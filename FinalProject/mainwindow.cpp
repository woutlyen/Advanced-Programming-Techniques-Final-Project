#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->setCentralWidget(ui->graphicsView);
}

void MainWindow::setScene(QGraphicsScene *scene)
{
    ui->graphicsView->setScene(scene);
}

void MainWindow::setScale(double sx, double sy) {
    int vs = ui->graphicsView->verticalScrollBar()->value();
    int hs = ui->graphicsView->horizontalScrollBar()->value();
    std::cout << vs << std::endl;
    std::cout << hs << std::endl;
    ui->graphicsView->setTransform(QTransform::fromScale(sx, sy));
    ui->graphicsView->verticalScrollBar()->setValue(vs);
    ui->graphicsView->horizontalScrollBar()->setValue(hs);
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::zoom(double zoomFactor) {
    ui->graphicsView->scale(zoomFactor, zoomFactor);
}
