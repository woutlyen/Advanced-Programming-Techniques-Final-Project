#include "mainwindow.h"
#include "Controller/levelcontroller.h"
#include "ui_mainwindow.h"
#include <QScrollBar>

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

void MainWindow::setScene()
{
    LevelController& levelController = LevelController::getInstance();
    ui->graphicsView2D->setScene(levelController.getCurrentLevel().scenes2D);
    ui->graphicsViewText->setScene(levelController.getCurrentLevel().scenesText);
}

void MainWindow::setScale(double sx, double sy) {
    int vs = ui->graphicsView2D->verticalScrollBar()->value();
    int hs = ui->graphicsView2D->horizontalScrollBar()->value();

    ui->graphicsView2D->setTransform(QTransform::fromScale(sx, sy));
    ui->graphicsView2D->verticalScrollBar()->setValue(vs);
    ui->graphicsView2D->horizontalScrollBar()->setValue(hs);

    ui->graphicsViewText->setTransform(QTransform::fromScale(sx, sy));
    ui->graphicsViewText->verticalScrollBar()->setValue(vs);
    ui->graphicsViewText->horizontalScrollBar()->setValue(hs);
}


void MainWindow::updateConnections()
{
    LevelController& levelController = LevelController::getInstance();

    disconnect(this, nullptr, nullptr, nullptr);
    connect(levelController.getCurrentLevel().protagonist.get(), &Player::healthChanged, this, &MainWindow::updateHealthBar);
    connect(levelController.getCurrentLevel().protagonist.get(), &Player::energyChanged, this, &MainWindow::updateEnergyBar);

    updateEnergyBar(static_cast<int>(levelController.getCurrentLevel().protagonist->getEnergy()));
    updateHealthBar(static_cast<int>(levelController.getCurrentLevel().protagonist->getHealth()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::zoomIn()
{
    if (currentZoomLevel < 10) { // Limit maximum zoom in
        ui->graphicsView2D->scale(zoomFactor, zoomFactor);
        ui->graphicsViewText->scale(zoomFactor, zoomFactor);
        ++currentZoomLevel;
    }
}

void MainWindow::zoomOut()
{
    if (currentZoomLevel > -10) { // Limit maximum zoom out
        ui->graphicsView2D->scale(1/zoomFactor, 1/zoomFactor);
        ui->graphicsViewText->scale(1/zoomFactor, 1/zoomFactor);
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
        color = "#0291d4";
    } else if (value > 25) {
        color = "#0272a6";
    } else {
        color = "#004b6e";
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
        color = "#bfc900";
    } else {
        color = "darkRed";
    }

    // Apply the new color
    ui->healthBar->setStyleSheet(QString("QProgressBar { border-radius: 10px; border: 2px solid #666; background: #ddd; } QProgressBar::chunk { background-color: %1; border-radius: 8px; }").arg(color));
}





