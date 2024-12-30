#include "enemyviewtext.h"
#include "qgraphicsitem.h"
#include "qpen.h"
#include "qtimer.h"

EnemyViewText::EnemyViewText(const std::unique_ptr<EnemyWrapper> &enemy, double tileWidth, double tileHeight, QFont font, QGraphicsItem *parent)
    : QObject(),
      QGraphicsSimpleTextItem(parent),
      animationTimer(new QTimer(this)),
      currentFrameIndex{0} {

    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->font = font;
    this->pen = QPen(QColor(60,180,120));
    this->pen.setWidthF(1.5);

    // TODO: Add color
    setText(".E.");
    setFont(this->font);
    setPen(pen);
    setPos(tileWidth * enemy->getXPos() + tileWidth / 4, tileHeight * enemy->getYPos() + tileHeight / 2);

    animationTimer->setInterval(30);
    animationTimer->start();

    connect(animationTimer, &QTimer::timeout, this, &EnemyViewText::updateAnimationFrame);
}

void EnemyViewText::updateAnimationFrame() {

    currentFrameIndex = (currentFrameIndex + 1) % 60;
    if (currentFrameIndex < 30) {
        setBrush((QColor(2 * currentFrameIndex, 6 * currentFrameIndex, 4 * currentFrameIndex)));

    } else {
        setBrush((QColor(60 - 2 * (currentFrameIndex - 30), 180 - 6 * (currentFrameIndex - 30), 120 - 4 * (currentFrameIndex - 30))));
    }
    // Force the object to update
    update();
}
