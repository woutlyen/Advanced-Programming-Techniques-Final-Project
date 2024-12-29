#include "healthpackviewtext.h"
#include "qgraphicsitem.h"
#include "qpen.h"
#include "qtimer.h"

HealthPackViewText::HealthPackViewText(const std::unique_ptr<Tile> &healthPack, double tileWidth, double tileHeight, QFont font, QGraphicsItem *parent)
    : QObject(),
      QGraphicsSimpleTextItem(parent),
      animationTimer(new QTimer(this)),
      beatCount{3} {

    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->font = font;

    // TODO: Add color
    setText("H");
    setFont(this->font);
    setPen(QColor(255, 0, 0));
    setBrush(QColor(255, 0, 0));
    setPos(tileWidth * healthPack->getXPos() + tileWidth / 2, tileHeight * healthPack->getYPos() + tileHeight / 2);

    animationTimer->setInterval(600);
    animationTimer->start();

    connect(animationTimer, &QTimer::timeout, this, &HealthPackViewText::updateAnimationFrame);
}

void HealthPackViewText::updateAnimationFrame() {

    // Switch if the font is bold or not
    this->font.setBold(!this->font.bold());
    setFont(this->font);

    // Force the object to update
    update();

    // Create heartbeat animation
    beatCount = (++beatCount) % 4;
    animationTimer->setInterval((beatCount == 3) ? 600 : 200);
}

void HealthPackViewText::playPickupAnimation() {
    QTimer *fadeTimer = new QTimer(this);
    connect(fadeTimer, &QTimer::timeout, this, [this, fadeTimer]() {
        double opacity = this->opacity();
        if (opacity <= 0) {
            // Diable timer
            fadeTimer->stop();
            fadeTimer->deleteLater();

            // Remove item
            delete this;
        } else {
            setOpacity(opacity - 0.02);
        }
    });
    fadeTimer->start(30);
}
