#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //this->setCentralWidget(ui->graphicsView);

    ui->energyBar->setRange(0, 100);  // Set the range of the bar
    ui->energyBar->setValue(100);     // Initialize at maximum value
    ui->energyBar->setTextVisible(false); // Hide text on the bar
    //ui->energyBar->setFixedSize(300, 20); // Set a fixed size
    ui->energyBar->setStyleSheet("QProgressBar::chunk { background-color: darkCyan; }");

    ui->healthBar->setRange(0, 100);  // Set the range of the bar
    ui->healthBar->setValue(100);     // Initialize at maximum value
    ui->healthBar->setTextVisible(false); // Hide text on the bar
    //ui->healthBar->setFixedSize(300, 20); // Set a fixed size
    ui->healthBar->setStyleSheet("QProgressBar::chunk { background-color: green; }");

}

void MainWindow::setScene(QGraphicsScene *scene)
{
    ui->graphicsView->setScene(scene);
}

void MainWindow::setScale(double sx, double sy) {
    int vs = ui->graphicsView->verticalScrollBar()->value();
    int hs = ui->graphicsView->horizontalScrollBar()->value();
    ui->graphicsView->setTransform(QTransform::fromScale(sx, sy));
    ui->graphicsView->verticalScrollBar()->setValue(vs);
    ui->graphicsView->horizontalScrollBar()->setValue(hs);
}


void MainWindow::updateConnections(std::unique_ptr<Player> &protagonist)
{
    disconnect(this, nullptr, nullptr, nullptr);
    connect(protagonist.get(), &Protagonist::healthChanged, this, &MainWindow::updateHealthBar);
    connect(protagonist.get(), &Protagonist::energyChanged, this, &MainWindow::updateEnergyBar);

    updateEnergyBar(static_cast<int>(protagonist->getEnergy()));
    updateHealthBar(static_cast<int>(protagonist->getHealth()));
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

void MainWindow::updateEnergyBar(int value)
{
    // Update the bar value
    ui->energyBar->setValue(value);

    // Change the color based on the value
    QString color;
    if (value > 50) {
        color = "darkCyan";
    } else if (value > 25) {
        color = "darkBlue";
    } else {
        color = "darkRed";
    }

    // Apply the new color
    ui->energyBar->setStyleSheet(QString("QProgressBar::chunk { background-color: %1; }").arg(color));
}

void MainWindow::updateHealthBar(int value)
{
    // Update the bar value
    ui->healthBar->setValue(value);

    // Change the color based on the value
    QString color;
    if (value > 50) {
        color = "green";
    } else if (value > 25) {
        color = "yellow";
    } else {
        color = "darkRed";
    }

    // Apply the new color
    ui->healthBar->setStyleSheet(QString("QProgressBar::chunk { background-color: %1; }").arg(color));
}





