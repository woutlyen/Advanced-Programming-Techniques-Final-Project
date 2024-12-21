#include "enemyviewtext.h"
#include "qgraphicsitem.h"
#include "qpen.h"
#include "qtimer.h"

EnemyViewText::EnemyViewText(const std::unique_ptr<Enemy> &enemy, double tileWidth, double tileHeight, QFont font, QGraphicsItem *parent)
    : QObject(),
      QGraphicsSimpleTextItem(parent),
      animationTimer(new QTimer(this)) {

    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->font = font;

    // TODO: Add color
    setText("E");
    setFont(this->font);
    setPen(QColor(0, 255, 0));
    setPos(tileWidth * enemy->getXPos() + tileWidth / 2, tileHeight * enemy->getYPos() + tileHeight / 2);

    animationTimer->setInterval(500);
    animationTimer->start();

    connect(animationTimer, &QTimer::timeout, this, &EnemyViewText::updateAnimationFrame);
}

void EnemyViewText::updateAnimationFrame() {

    // Switch if the font is bold or not
    this->font.setUnderline(!this->font.underline());
    setFont(this->font);

    // Force the object to update
    update();
}
