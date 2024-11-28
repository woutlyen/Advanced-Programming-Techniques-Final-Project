#include "worldviewtext.h"
#include "View/enemyviewtext.h"
#include "View/healthpackviewtext.h"
#include "qgraphicsitem.h"
#include <QObject>

#include "View/enemyview2d.h"
#include "View/healthpackview2d.h"
#include "View/protagonistviewtext.h"
#include "qgraphicsscene.h"

WorldViewText::WorldViewText() {}

QGraphicsScene *WorldViewText::makeScene(std::vector<std::unique_ptr<Enemy>> &enemies, std::vector<std::unique_ptr<Tile>> &healthPacks, std::unique_ptr<Protagonist> &protagonist, int rows, int columns, QString filename, std::size_t gridSize) {
    QGraphicsScene *scene = new QGraphicsScene();

    QFont font("monospace");
    font.setStyleHint(QFont::Monospace);
    font.setPixelSize(25);

    // Get the size of one tile for positioning other elements
    // Doesn't work well with unicode characters -> use +---\n| instead for consistent spacing
    auto tilesize = QGraphicsSimpleTextItem("+---\n");
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


    scene->addItem(new ProtagonistViewText(protagonist, width, height, font));

    healthBar = new StatusBar2D(10, 10, Qt::green);
    energyBar = new StatusBar2D(10, 40, Qt::green);

    QObject::connect(protagonist.get(), &Protagonist::healthChanged, healthBar, &StatusBar2D::updateBar);
    QObject::connect(protagonist.get(), &Protagonist::energyChanged, energyBar, &StatusBar2D::updateBar);

    scene->addItem(healthBar);
    scene->addItem(energyBar);

    return scene;
}
