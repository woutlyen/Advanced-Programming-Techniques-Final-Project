#include "penemyviewtext.h"
#include "qgraphicsitem.h"
#include "qpen.h"
#include "qtimer.h"

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

    // TODO: Add color
    setText("oEo");
    setFont(this->font);
    setPen(pen);
    setPos(tileWidth * enemy->getXPos() + tileWidth / 4, tileHeight * enemy->getYPos() + tileHeight / 2);

    animationTimer->setInterval(50);
    animationTimer->start();

    connect(animationTimer, &QTimer::timeout, this, &PEnemyViewText::updateAnimationFrame);
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
