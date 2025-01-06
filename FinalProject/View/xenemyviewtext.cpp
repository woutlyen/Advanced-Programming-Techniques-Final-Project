#include "xenemyviewtext.h"
#include "Model/xenemy.h"

XEnemyViewText::XEnemyViewText(const std::unique_ptr<EnemyWrapper> &enemy, double tileWidth, double tileHeight, QFont font)
    : EnemyViewText(enemy, tileWidth, tileHeight, font),
      transformed{false} {

    // Only change pen color, other fields are set in EnemyViewText constructor
    this->pen = QPen(QColor(60, 180, 120));
    this->pen.setWidthF(1);
    setPen(pen);

    connect(enemy.get(), &EnemyWrapper::dead, this, &XEnemyViewText::onDefeated);
    connect(static_cast<XEnemy *>(enemy.get()), &XEnemy::transform, this, &XEnemyViewText::onTransform);
}

void XEnemyViewText::setAnimation() {
    switch (currentState) {
    case Idle:
        if (this->transformed) {
            setBrush(QColor(0, 0, 0));
            setText("xEx");
            if (currentFrameIndex < 32) {
                this->pen.setColor(QColor(255 - 3 * currentFrameIndex, 255 - 3 * currentFrameIndex, 255 - 3 * currentFrameIndex));
                setPen(this->pen);

            } else {
                this->pen.setColor(QColor(4 * (currentFrameIndex), 4 * (currentFrameIndex), 4 * (currentFrameIndex)));
                setPen(this->pen);
            }
        } else {
            setText(".E.");
            if (currentFrameIndex < 30) {
                setBrush(QColor(2 * currentFrameIndex, 6 * currentFrameIndex, 4 * currentFrameIndex));

            } else {
                setBrush(QColor(60 - 2 * (currentFrameIndex - 30), 180 - 6 * (currentFrameIndex - 30), 120 - 4 * (currentFrameIndex - 30)));
            }
        }
        // Force the object to update
        update();
        break;

    case Fighting:
        break;

    case Dying:
        setText(".x.");
        setBrush(QColor(0, 0, 0));
        break;

    case Walking:
        break;
    }
}

void XEnemyViewText::onDefeated() {
    if (!transformed) {
        transformed = true;
        setState(Idle);
    } else {
        setState(Dying);
    }
}

void XEnemyViewText::onTransform() {
    if (!transformed) {
        transformed = true;
    }
}
