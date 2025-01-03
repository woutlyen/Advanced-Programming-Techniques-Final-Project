#include "penemyviewtext.h"
#include "Controller/levelcontroller.h"
#include "qgraphicsitem.h"
#include "qpen.h"
#include "qtextdocument.h"
#include "qtimer.h"
#include <iostream>

PEnemyViewText::PEnemyViewText(const std::unique_ptr<EnemyWrapper> &enemy, double tileWidth, double tileHeight, QFont font, QGraphicsItem *parent)
    : QObject(),
      QGraphicsSimpleTextItem(parent),
      animationTimer(new QTimer(this)),
      currentFrameIndex{0} {

    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->font = font;
    this->pen = QPen(QColor(216, 145, 239));
    this->pen.setWidthF(1.5);
    this->poisonCircle = new QGraphicsTextItem;
    this->died = false;

    setText("oEo");
    setFont(this->font);
    setPen(pen);
    setPos(tileWidth * enemy->getXPos() + tileWidth / 4, tileHeight * enemy->getYPos() + tileHeight / 2);

    animationTimer->setInterval(50);
    animationTimer->start();

    connect(animationTimer, &QTimer::timeout, this, &PEnemyViewText::updateAnimationFrame);
    connect(enemy.get(), &EnemyWrapper::dead, this, &PEnemyViewText::onDefeated);
    connect(static_cast<PEnemyWrapper *>(enemy.get()), &PEnemyWrapper::startPoison, this, &PEnemyViewText::setPoisonCircle);
    connect(static_cast<PEnemyWrapper *>(enemy.get()), &PEnemyWrapper::poisonLevelUpdated, this, &PEnemyViewText::onPoisonLevelValueUpdated);
}

void PEnemyViewText::updateAnimationFrame() {

    currentFrameIndex = (currentFrameIndex + 1) % 50;
    if (currentFrameIndex < 25) {
        setBrush((QColor(9 * currentFrameIndex, 6 * currentFrameIndex, 9 * currentFrameIndex)));

    } else {
        setBrush((QColor(225 - 9 * (currentFrameIndex - 25), 150 - 6 * (currentFrameIndex - 25), 225 - 9 * (currentFrameIndex - 25))));
    }
    // Force the object to update
    update();
}

void PEnemyViewText::onDefeated() {
    if (!died) {
        died = true;
        setText(".o.");
        disconnect(animationTimer, &QTimer::timeout, this, &PEnemyViewText::updateAnimationFrame);
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
