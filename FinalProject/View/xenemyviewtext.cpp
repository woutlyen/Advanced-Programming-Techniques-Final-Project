#include "xenemyviewtext.h"
#include "qgraphicsitem.h"
#include "qpen.h"
#include "qtimer.h"

XEnemyViewText::XEnemyViewText(const std::unique_ptr<EnemyWrapper> &enemy, double tileWidth, double tileHeight, QFont font, QGraphicsItem *parent)
    : QObject(),
      QGraphicsSimpleTextItem(parent),
      animationTimer(new QTimer(this)),
      currentFrameIndex{0} {

    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->font = font;
    this->pen = QPen(QColor(255, 255, 255));

    // TODO: Add color
    setText("xEx");
    setFont(this->font);
    setPen(pen);
    setPos(tileWidth * enemy->getXPos() + tileWidth / 4, tileHeight * enemy->getYPos() + tileHeight / 2);

    animationTimer->setInterval(30);
    animationTimer->start();

    connect(animationTimer, &QTimer::timeout, this, &XEnemyViewText::updateAnimationFrame);
}

void XEnemyViewText::updateAnimationFrame() {

    // Switch if the font is bold or not
    currentFrameIndex = (currentFrameIndex + 1) % 64;
    if (currentFrameIndex < 32) {
        this->pen.setColor((QColor(255 - 3 * currentFrameIndex, 255 - 3 * currentFrameIndex, 255 - 3 * currentFrameIndex)));
        setPen(this->pen);

    } else {
        this->pen.setColor((QColor(4 * (currentFrameIndex), 4 * (currentFrameIndex), 4 * (currentFrameIndex ))));
        setPen(this->pen);
    }
    // Force the object to update
    update();
}
