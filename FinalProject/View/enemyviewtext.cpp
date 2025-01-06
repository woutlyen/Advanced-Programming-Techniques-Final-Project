#include "enemyviewtext.h"

EnemyViewText::EnemyViewText(const std::unique_ptr<EnemyWrapper> &enemy, double tileWidth, double tileHeight, QFont font)
    : GameObjectTextView(tileWidth, tileHeight, font), enemy(enemy) {

    this->pen = QPen(QColor(60, 180, 120));
    this->pen.setWidthF(1.5);

    setText(".E.");
    setPen(pen);
    setPos(tileWidth * enemy->getXPos() + tileWidth / 4, tileHeight * enemy->getYPos() + tileHeight / 2);

    animationTimer->setInterval(30);
    animationTimer->start();

    connectAnimationTimer();
    connect(enemy.get(), &EnemyWrapper::dead, this, &EnemyViewText::onDefeated);
    setState(Idle);
}

void EnemyViewText::setAnimation() {
    switch (currentState) {
    case Idle:
        setText(".E.");
        if (currentFrameIndex < 30) {
            setBrush((QColor(2 * currentFrameIndex, 6 * currentFrameIndex, 4 * currentFrameIndex)));

        } else {
            setBrush((QColor(60 - 2 * (currentFrameIndex - 30), 180 - 6 * (currentFrameIndex - 30), 120 - 4 * (currentFrameIndex - 30))));
        }
        // Force the object to update
        update();
        break;

    case Fighting:
        break;

    case Dying:
        setText(".-.");
        setBrush(QColor(0,0,0));
        break;

    case Walking:
        break;
    }
}

void EnemyViewText::onDefeated() {
    if(currentState != Dying) {
        setState(Dying);
    }
}
