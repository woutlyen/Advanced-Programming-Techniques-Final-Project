#include "penemyviewtext.h"
#include "Controller/levelcontroller.h"
#include "qgraphicsitem.h"
#include "qpen.h"
#include "qtextdocument.h"
#include "qtimer.h"
#include <iostream>

PEnemyViewText::PEnemyViewText(const std::unique_ptr<EnemyWrapper> &enemy, double tileWidth, double tileHeight, QFont font)
    : EnemyViewText(enemy, tileWidth, tileHeight, font) {

    this->poisonCircle = new QGraphicsTextItem;
    this->died = false;

    QPen pen(QColor(216, 145, 239));
    pen.setWidthF(1.5);

    setPen(pen);
    setText("oEo");

    animationTimer->setInterval(50);
    animationTimer->start();

    connect(enemy.get(), &EnemyWrapper::dead, this, &PEnemyViewText::onDefeated);
    connect(static_cast<PEnemyWrapper *>(enemy.get()), &PEnemyWrapper::startPoison, this, &PEnemyViewText::setPoisonCircle);
    connect(static_cast<PEnemyWrapper *>(enemy.get()), &PEnemyWrapper::poisonLevelUpdated, this, &PEnemyViewText::onPoisonLevelValueUpdated);
}

void PEnemyViewText::setAnimation() {
    switch (currentState) {
    case Idle:
        setText("oEo");
        if (currentFrameIndex < 25) {
            setBrush((QColor(9 * currentFrameIndex, 6 * currentFrameIndex, 9 * currentFrameIndex)));

        } else {
            setBrush((QColor(225 - 9 * (currentFrameIndex - 25), 150 - 6 * (currentFrameIndex - 25), 225 - 9 * (currentFrameIndex - 25))));
        }
        // Force the object to update
        update();
        break;

    case Fighting:
        break;

    case Dying:
        setText(".o.");
        break;

    case Walking:
        break;
    }
}

void PEnemyViewText::onDefeated() {
    if (currentState != Dying) {
        setState(Dying);
        QTimer::singleShot(2000, this, [this]() { LevelController::getInstance().removePoisonedCircle(poisonCircle); });
    }
}

void PEnemyViewText::setPoisonCircle(int value) {
    poisonCircle = LevelController::getInstance().generatePoisonedTextArea(x(), y(), value);
    QTimer::singleShot(2000, this, [this, value]() {
        expandPoisonCircle(value);
    });
}

void PEnemyViewText::expandPoisonCircle(int value) {
    auto boxSize = QGraphicsSimpleTextItem("\u2588");
    boxSize.setFont(font);
    double boxWidth = boxSize.boundingRect().width();
    double boxHeight = boxSize.boundingRect().height();

    QString text;
    text.append("<p style=\"line-height:0.5\">");
    text.append("<font color=\"");
    text.append(QColor(83, 0, 128, (value * 255) / 100).name(QColor::HexArgb));
    text.append("\">");
    for (int i = 0; i <= 5 * 4 + 1; ++i) {
        for (int j = 0; j <= 5 * 4 + 1; ++j) {
            if ((j - 10.5) * (j - 10.5) + (i - 10.5) * (i - 10.5) < 10.5 * 10.5)
                text.append("\u2585");
            else
                // Use non breakin space because other whiteline characters
                // get removed at the front of html text
                text.append("\u00A0");
        }
        text.append("<br>");
    }
    text.append("</font></p>");
    poisonCircle->setHtml(text);

    // Recenter the text on the penemy
    poisonCircle->moveBy(-boxWidth * 4, -boxHeight * 2);
}

void PEnemyViewText::onPoisonLevelValueUpdated(int value) {

    // Reuse the blockcharachters to prevent regenerating the circle again
    // Paste the html color in front of it again with updated color
    QString text;
    text.append("<p style=\"line-height:0.5\">");
    text.append("<font color=\"");
    text.append(QColor(83, 0, 128, (value * 255) / 100).name(QColor::HexArgb));
    text.append("\">");

    // toPlainText() converts \u00A0 (no-break spaces) to \u0020 (regular space)
    // but regular spaces get removed at the beginning of a line so replace them back
    // and replace the \n with html's <br>
    text.append(poisonCircle->toPlainText().replace("\n", "<br>").replace("\u0020", "\u00A0"));
    text.append("</font></p>");
    poisonCircle->setHtml(text);
}
