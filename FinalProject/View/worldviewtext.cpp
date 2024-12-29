#include "worldviewtext.h"
#include "Controller/levelcontroller.h"
#include "Model/xenemy.h"
#include "View/enemyviewtext.h"
#include "View/healthpackviewtext.h"
#include "View/penemyviewtext.h"
#include "View/protagonistviewtext.h"
#include "View/xenemyviewtext.h"
#include "qobject.h"
#include <iostream>

WorldViewText::WorldViewText() : QObject() {

    font.setStyleHint(QFont::Monospace);
    font.setPixelSize(25);

    bgText1 = new QGraphicsTextItem();
    borders = new QGraphicsSimpleTextItem();

    bgText1->setZValue(-2);
    borders->setZValue(-1);

    // Make sure size is even, otherwise int divisions break
    if (size % 2)
        --size;
}

QGraphicsScene *WorldViewText::makeScene() const {
    LevelController &levelController = LevelController::getInstance();
    Level &level = levelController.getCurrentLevel();
    int rows = level.height;
    int columns = level.width;

    QGraphicsScene *scene = new QGraphicsScene();
    /*QObject::connect(level.protagonist.get(), &Protagonist::posChanged, this, &WorldViewText::updateGrid);*/
    connect(level.protagonist.get(), &Protagonist::posChanged, this, &WorldViewText::updateGrid);

    // Get the size of a box character
    auto boxSize = QGraphicsSimpleTextItem("\u2588");
    boxSize.setFont(font);
    double boxWidth = boxSize.boundingRect().width();
    double boxHeight = boxSize.boundingRect().height();

    // Get the size of one tile for positioning other elements
    // Doesn't work well with unicode characters -> use +---\n| instead for consistent spacing
    auto tilesize = QGraphicsSimpleTextItem("\u2588\u2588\u2588\u2588\n");
    tilesize.setFont(font);
    double width = tilesize.boundingRect().width();
    double height = tilesize.boundingRect().height();

    int xpos = 1;
    int ypos = 1;

    bgText1->setFont(font);
    bgText1->setHtml(pixmapToString(QPixmap(level.data_map), size, size));
    bgText1->setPos(boxWidth / 4 + width * xpos, boxHeight / 2 + height * ypos);

    scene->addItem(bgText1);
    /*scene->addItem(bgText2);*/

    QString border = "";

    if (rows > size)
        rows = size;
    if (columns > size)
        columns = size;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (i == 0) {
                if (j == 0)
                    border += QString("\u256d\u2500\u2500\u2500");
                else
                    border += QString("\u252c\u2500\u2500\u2500");
            } else {
                if (j == 0)
                    border += QString("\u251c\u2500\u2500\u2500");
                else
                    border += QString("\u253c\u2500\u2500\u2500");
            }
        }
        if (i == 0)
            border += QString("\u256e\n");
        else
            border += QString("\u2524\n");
        for (int j = 0; j < columns; j++) {
            border += QString("\u2502\u2002\u2002\u2002");
        }
        border += QString("\u2502\n");
    }
    for (int j = 0; j < columns; j++) {
        if (j == 0)
            border += QString("\u2570\u2500\u2500\u2500");
        else
            border += QString("\u2534\u2500\u2500\u2500");
    }
    border += QString("\u256f\n");

    borders->setText(border);
    borders->setFont(font);
    borders->setBrush(QBrush(QColor(150, 150, 100)));
    borders->setPos(width * xpos, height * ypos);

    scene->addItem(borders);

    for (auto &enemy : level.enemies) {
        if (dynamic_cast<PEnemy *>(enemy.get())) {
            scene->addItem(new PEnemyViewText(enemy, width, height, font));
        } else if (dynamic_cast<XEnemy *>(enemy.get())) {
            scene->addItem(new XEnemyViewText(enemy, width, height, font));
        } else {
            scene->addItem(new EnemyViewText(enemy, width, height, font));
        }
    }

    // Create and add healthpacks
    for (auto &pack : level.healthPacks) {
        scene->addItem(new HealthPackViewText(pack, width, height, font));
    }

    /**/
    /*for (int i = 0; i < rows; i++) {*/
    /*    for (int j = 0; j < columns; j++) {*/
    /*        auto text = scene->addSimpleText("\u250c\u2500\u2500\u2510\n\u2514\u2500\u2500\u2518",  font);*/
    /*        text->setPos(i*width + boxWidth/2, j*height + boxHeight/2);*/
    /*    }*/
    /*}*/

    scene->addItem(new ProtagonistViewText(level.protagonist, width, height, font));

    return scene;
}

void WorldViewText::updateGrid(int xPos, int yPos) {
    LevelController &levelController = LevelController::getInstance();
    Level &level = levelController.getCurrentLevel();

    if (level.scenesText != borders->scene()) {
        level.scenesText->addItem(bgText1);
        /*level.scenesText->addItem(bgText2);*/
        /*level.scenesText->addItem(bgText3);*/
        /*level.scenesText->addItem(bgText4);*/
        level.scenesText->addItem(borders);
    }

    // Get the size of one tile for positioning other elements
    // Doesn't work well with unicode characters -> use +---\n| instead for consistent spacing
    auto tilesize = QGraphicsSimpleTextItem("\u2588\u2588\u2588\u2588\n");
    tilesize.setFont(font);
    double width = tilesize.boundingRect().width();
    double height = tilesize.boundingRect().height();

    // Get the size of a box character
    auto boxSize = QGraphicsSimpleTextItem("\u2588");
    boxSize.setFont(font);
    double boxWidth = boxSize.boundingRect().width();
    double boxHeight = boxSize.boundingRect().height();

    int xBegin, yBegin;
    if (xPos - size / 2 < 0) {
        xBegin = 0;
    } else if (xPos + size / 2 > level.width) {
        xBegin = (level.width - size > 0) ? level.width - size : 0;
    } else {
        xBegin = xPos - size / 2;
    }

    if (yPos - size / 2 < 0) {
        yBegin = 0;
    } else if (yPos + size / 2 > level.height) {
        yBegin = (level.height - size > 0) ? level.height - size : 0;
    } else {
        yBegin = yPos - size / 2;
    }

    bgText1->setHtml(pixmapToString(QPixmap(level.visual_map).scaled(level.width * 4, level.height * 4), xPos, yPos));
    bgText1->setPos(boxWidth / 4 + width * xBegin, height * yBegin);

    borders->setPos(width * xBegin, height * yBegin);
}

QString WorldViewText::pixmapToString(const QPixmap &pixmap, int xPos, int yPos) const {

    QString bgText;

    // Convert the QPixmap to QImage for pixel manipulation
    QImage image = pixmap.toImage();

    // Ensure the image is in a format we can manipulate
    image = image.convertToFormat(QImage::Format_ARGB32);

    int xBegin, yBegin, xEnd, yEnd;
    xBegin = xPos * 4 - size * 4 / 2;
    yBegin = yPos * 4 - size * 4 / 2;
    xEnd = xPos * 4 + size * 4 / 2;
    yEnd = yPos * 4 + size * 4 / 2;
    if (xBegin < 0) {
        xBegin = 0;
        xEnd = size * 4;
    }
    if (yBegin < 0) {
        yBegin = 0;
        yEnd = size * 4;
    }
    if (xEnd > image.width()) {
        xBegin = image.width() - size * 4;
        if (xBegin < 0)
            xBegin = 0;
        xEnd = image.width();
    }
    if (yEnd > image.height()) {
        yBegin = image.height() - size * 4;
        if (yBegin < 0)
            yBegin = 0;
        yEnd = image.height();
    }
    // Loop through each pixel
    bgText.append("<p style=\"line-height:0.5\">");
    for (int y = yBegin; y < image.height() && (y < yEnd); ++y) {
        for (int x = xBegin; x < image.width() && (x < xEnd); ++x) {
            // Get the current pixel color
            QColor color = QColor(image.pixel(x, y));

            bgText.append("<font color=\"");
            bgText.append(color.name());
            bgText.append("\">\u2585</font>");
        }
        bgText.append("<br>");
    }
    bgText.append("</p>");
    return bgText;
}

void WorldViewText::setSize(int newSize) {
    this->size = newSize;
}
