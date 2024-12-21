#include "worldviewtext.h"
#include "Model/player.h"
#include "View/enemyviewtext.h"
#include "View/healthpackviewtext.h"
#include "qgraphicsitem.h"
#include <QObject>
#include <iostream>

#include "View/enemyview2d.h"
#include "View/healthpackview2d.h"
#include "View/protagonistviewtext.h"
#include "qgraphicsscene.h"

WorldViewText::WorldViewText() {}

QGraphicsScene *WorldViewText::makeScene(std::vector<std::unique_ptr<Enemy>> &enemies, std::vector<std::unique_ptr<Tile>> &healthPacks, std::unique_ptr<Player> &protagonist, int rows, int columns, QString filename, std::size_t gridSize) {
    QGraphicsScene *scene = new QGraphicsScene();

    QFont font("Monospace");
    font.setStyleHint(QFont::Monospace);
    font.setPixelSize(25);

    auto boxSize = QGraphicsSimpleTextItem("\u2588");
    boxSize.setFont(font);
    double boxWidth = boxSize.boundingRect().width();
    double boxHeight = boxSize.boundingRect().height();

    auto bgText = scene->addText("", font);
    bgText->setHtml(pixmapToString(QPixmap(filename)));
    bgText->setPos(boxWidth/4, boxHeight/2);
    auto bgText2 = scene->addText("", font);
    bgText2->setHtml(pixmapToString(QPixmap(filename)));
    bgText2->setPos(boxWidth/4, boxHeight/3);

    // Get the size of one tile for positioning other elements
    // Doesn't work well with unicode characters -> use +---\n| instead for consistent spacing
    auto tilesize = QGraphicsSimpleTextItem("\u2588\u2588\u2588\u2588\n");
    tilesize.setFont(font);
    double width = tilesize.boundingRect().width();
    double height = tilesize.boundingRect().height();

    auto borders = scene->addSimpleText(QString(), font);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (i == 0) {
                if (j == 0)
                    borders->setText(borders->text() + QString("\u250c\u2500\u2500\u2500"));
                else
                    borders->setText(borders->text() + QString("\u252c\u2500\u2500\u2500"));
            } else {
                if (j == 0)
                    borders->setText(borders->text() + QString("\u251c\u2500\u2500\u2500"));
                else
                    borders->setText(borders->text() + QString("\u253c\u2500\u2500\u2500"));
            }
        }
        if (i == 0)
            borders->setText(borders->text() + QString("\u2501\n"));
        else
            borders->setText(borders->text() + QString("\u2524\n"));
        for (int j = 0; j < columns; j++) {
            borders->setText(borders->text() + QString("\u2502\u2002\u2002\u2002"));
        }
        borders->setText(borders->text() + QString("\u2502\n"));
    }
    for (int j = 0; j < columns; j++) {
        if (j == 0)
            borders->setText(borders->text() + QString("\u2570\u2500\u2500\u2500"));
        else
            borders->setText(borders->text() + QString("\u2534\u2500\u2500\u2500"));
    }
    borders->setText(borders->text() + QString("\u256f\n"));

    // Place protagonist, enemies and health
    /*auto prot = scene->addSimpleText(QString("P"), font);*/
    /*prot->setPen(QColor(255, 205, 0));*/
    /*prot->setPos(width * protagonist->getXPos() + width / 2, height * protagonist->getXPos() + height / 2);*/

    for (auto &enemy : enemies) {
        scene->addItem(new EnemyViewText(enemy, width, height, font));
    }

    for (auto &pack : healthPacks) {
        scene->addItem(new HealthPackViewText(pack, width, height, font));
    }


    /**/
    /*for (int i = 0; i < rows; i++) {*/
    /*    for (int j = 0; j < columns; j++) {*/
    /*        auto text = scene->addSimpleText("\u250c\u2500\u2500\u2510\n\u2514\u2500\u2500\u2518",  font);*/
    /*        text->setPos(i*width + boxWidth/2, j*height + boxHeight/2);*/
    /*    }*/
    /*}*/

    scene->addItem(new ProtagonistViewText(protagonist, width, height, font));

    /*
    healthBar = new StatusBar2D(10, 10, Qt::green);
    energyBar = new StatusBar2D(10, 40, Qt::green);

    QObject::connect(protagonist.get(), &Protagonist::healthChanged, healthBar, &StatusBar2D::updateBar);
    QObject::connect(protagonist.get(), &Protagonist::energyChanged, energyBar, &StatusBar2D::updateBar);

    scene->addItem(healthBar);
    scene->addItem(energyBar);
    */

    return scene;
}

QString WorldViewText::pixmapToString(const QPixmap &pixmap) {

    QString bgText;
    QColor bgColor;

    // Convert the QPixmap to QImage for pixel manipulation
    QImage image = pixmap.toImage();

    // Ensure the image is in a format we can manipulate
    image = image.convertToFormat(QImage::Format_ARGB32);

    // Loop through each pixel
    for (int y = 0; y/2 < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            // Get the current pixel color
            QColor color = QColor(image.pixel(x, y/2));

            // Calculate the intensity (grayscale value)
            int intensity = qGray(color.red(), color.green(), color.blue()); // Convert to grayscale intensity (0-255)
            int red = darkGreen.red() + (lightGreen.red() - darkGreen.red()) * intensity / 255;
            int green = darkGreen.green() + (lightGreen.green() - darkGreen.green()) * intensity / 255;
            int blue = darkGreen.blue() + (lightGreen.blue() - darkGreen.blue()) * intensity / 255;

            // Set the new color

            bgColor.fromRgb(red, green, blue);
            bgText.append("<font color=\"");
            /*bgText.append("#00FF00");*/
            bgText.append(QColor(red, green, blue).name());
            bgText.append("\">\u2588\u2588\u2588\u2588</font>");
        }
        bgText.append("<br>");
    }

    return bgText;
}

QPixmap WorldViewText::recolorGrayscalePixmap(const QPixmap &pixmap) {
    // Convert the QPixmap to QImage for pixel manipulation
    QImage image = pixmap.toImage();

    // Ensure the image is in a format we can manipulate
    image = image.convertToFormat(QImage::Format_ARGB32);

    // Loop through each pixel
    for (int y = 0; y/2 < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            // Get the current pixel color
            QColor color = QColor(image.pixel(x, y/2));

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
