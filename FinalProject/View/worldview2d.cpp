#include "worldview2d.h"

#include "Model/xenemy.h"

#include "View/enemyview2d.h"
#include "View/penemyview2d.h"
#include "View/xenemyview2d.h"

#include "View/healthpackview2d.h"
#include "View/protagonistview2d.h"

#include <QGraphicsScene>


WorldView2D::WorldView2D() {}

QGraphicsScene *WorldView2D::makeScene(std::vector<std::unique_ptr<Enemy> > &enemies, std::vector<std::unique_ptr<Tile> > &healthPacks, std::unique_ptr<Player> &protagonist, int rows, int columns, QString filename, std::size_t gridSize)
{
    QGraphicsScene* scene = new QGraphicsScene();

    /*scene->addPixmap(recolorGrayscalePixmap(QPixmap(filename))
                         .scaled(gridSize*QPixmap(filename).width(),
                                 gridSize*QPixmap(filename).height(),
                                 Qt::KeepAspectRatio));*/

    scene->addPixmap(recolorGrayscalePixmap(QPixmap(filename)))->setScale(64.0);

    // Create and add health views
    for (const auto& healthPack : healthPacks) {
        scene->addItem(new HealthPackView2D(healthPack,gridSize));
    }

    // Create and add enemy views
    for (const auto& enemy : enemies) {

        if (dynamic_cast<PEnemy*>(enemy.get())) {
            // If the enemy is of type PEnemy
            scene->addItem(new PEnemyView2D(enemy, gridSize));
        } else if (dynamic_cast<XEnemy*>(enemy.get())) {
            // If the enemy is of type XEnemy
            scene->addItem(new XEnemyView2D(enemy, gridSize));
        } else {
            // If the enemy is of type Enemy
            scene->addItem(new EnemyView2D(enemy, gridSize));
        }
    }

    // Create and add protagonist view
    scene->addItem(new ProtagonistView2D(protagonist,gridSize));

    healthBar = new StatusBar2D(10, 10, Qt::green);
    energyBar = new StatusBar2D(10, 40, Qt::green);

    connect(protagonist.get(), &Protagonist::healthChanged, healthBar, &StatusBar2D::updateBar);
    connect(protagonist.get(), &Protagonist::energyChanged, energyBar, &StatusBar2D::updateBar);

    scene->addItem(healthBar);
    scene->addItem(energyBar);

    return scene;
}

QPixmap WorldView2D::recolorGrayscalePixmap(const QPixmap& pixmap) {
    // Convert the QPixmap to QImage for pixel manipulation
    QImage image = pixmap.toImage();

    // Ensure the image is in a format we can manipulate
    image = image.convertToFormat(QImage::Format_ARGB32);

    // Loop through each pixel
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            // Get the current pixel color
            QColor color = QColor(image.pixel(x, y));

            // Calculate the intensity (grayscale value)
            int intensity = qGray(color.red(), color.green(), color.blue()); // Convert to grayscale intensity (0-255)

            // Interpolate between darkGreen and lightGreen based on intensity
            int red = darkGreen.red() + (lightGreen.red() - darkGreen.red()) * intensity / 255;
            int green = darkGreen.green() + (lightGreen.green() - darkGreen.green()) * intensity / 255;
            int blue = darkGreen.blue() + (lightGreen.blue() - darkGreen.blue()) * intensity / 255;

            // Set the new color
            image.setPixelColor(x, y, QColor(red, green, blue));
        }
    }

    // Convert the modified QImage back to QPixmap
    return QPixmap::fromImage(image);
}
