#include "worldviewtext.h"
#include "View/protagonistviewtext.h"
#include "qgraphicsitem.h"

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
    auto prot = scene->addSimpleText(QString("P"), font);
    prot->setPen(QColor(255, 205, 0));
    prot->setPos(width * protagonist->getXPos() + width / 2, height * protagonist->getXPos() + height / 2);

    for (auto &enemy : enemies) {
        auto e = scene->addSimpleText(QString("E"), font);
        e->setPen(QColor(0, 255, 0));
        e->setPos(width * enemy->getXPos() + width / 2, height * enemy->getYPos() + height / 2);
    }

    for (auto &pack : healthPacks) {
        auto h = scene->addSimpleText(QString("H"), font);
        h->setPen(QColor(255, 0, 0));
        h->setPos(width * pack->getXPos() + width / 2, height * pack->getYPos() + height / 2);
    }

    scene->addItem(new ProtagonistViewText(protagonist, gridSize));

    return scene;
}
