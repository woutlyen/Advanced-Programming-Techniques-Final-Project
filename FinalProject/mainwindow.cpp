#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //this->setCentralWidget(ui->graphicsView);

    ui->energyBar->setRange(0, 100);
    ui->energyBar->setValue(0);
    ui->energyBar->setTextVisible(false);

    ui->healthBar->setRange(0, 100);
    ui->healthBar->setValue(0);
    ui->healthBar->setTextVisible(false);

    ui->zoomOut->setFixedSize(50, 50);
    ui->zoomOut->setStyleSheet(
        "QPushButton {"
        "   border-radius: 25px;" // Rounded corners (circle effect for square buttons)
        "   background-color: #f44336;" // Red background
        "   color: white;" // White text
        "   font-size: 18px;" // Larger font
        "}"
        "QPushButton:hover {"
        "   background-color: #e53935;" // Slightly darker red on hover
        "}"
        "QPushButton:pressed {"
        "   background-color: #d32f2f;" // Even darker red when pressed
        "}"
    );

    ui->zoomIn->setFixedSize(50, 50);
    ui->zoomIn->setStyleSheet(
        "QPushButton {"
        "   border-radius: 25px;" // Rounded corners (circle effect for square buttons)
        "   background-color: #4CAF50;" // Green background
        "   color: white;" // White text
        "   font-size: 18px;" // Larger font
        "}"
        "QPushButton:hover {"
        "   background-color: #45a049;" // Slightly darker green on hover
        "}"
        "QPushButton:pressed {"
        "   background-color: #3e8e41;" // Even darker green when pressed
        "}"
    );
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
    ui->energyBar->setStyleSheet(QString("QProgressBar { border-radius: 10px; border: 2px solid #666; background: #ddd; } QProgressBar::chunk { background-color: %1; border-radius: 8px; }").arg(color));
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
    ui->healthBar->setStyleSheet(QString("QProgressBar { border-radius: 10px; border: 2px solid #666; background: #ddd; } QProgressBar::chunk { background-color: %1; border-radius: 8px; }").arg(color));
}





