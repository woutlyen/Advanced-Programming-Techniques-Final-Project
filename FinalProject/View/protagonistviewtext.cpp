#include "protagonistviewtext.h"
#include "healthpackviewtext.h"
#include "qgraphicseffect.h"

#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QScrollBar>

ProtagonistViewText::ProtagonistViewText(const std::unique_ptr<Player> &protagonist, double tileWidth, double tileHeight, QFont font)
    : GameObjectTextView(tileWidth, tileHeight, font),
      movementAnimation(new QPropertyAnimation(this, "pos")),
      poisonTimer(new QTimer(this)) {

    this->pen = QPen(QColor(255, 255, 0));

    // Set the initial pixmap
    setText(QString("{P}"));
    setPen(pen);
    setPos(tileWidth * protagonist->getXPos() + tileWidth / 4, tileHeight * protagonist->getYPos() + tileHeight / 2);

    // Connect signalsc & slots
    connect(protagonist.get(), &Player::posChanged, this, &ProtagonistViewText::onPositionChanged);
    connect(protagonist.get(), &Player::healthChanged, this, &ProtagonistViewText::onHealthChanged);
    connect(protagonist.get(), &Player::energyChanged, this, &ProtagonistViewText::onEnergyChanged);
    connect(protagonist.get(), &Player::playerAttack, this, &ProtagonistViewText::onPlayerAttack);
    connect(protagonist.get(), &Player::directionChanged, this, &ProtagonistViewText::onDirectionChanged);

    // Configure the movement animation
    movementAnimation->setDuration(480); // Animation duration (in milliseconds)
    movementAnimation->setEasingCurve(QEasingCurve::Linear);

    // Configure the animation timer
    animationTimer->setInterval(100); // Frame switch interval (in milliseconds)
    animationTimer->start();
    connect(animationTimer, &QTimer::timeout, this, &ProtagonistViewText::updateAnimationFrame);
    connect(movementAnimation, &QPropertyAnimation::finished, this, [this]() {
        if (currentState == Walking) {
            animationTimer->setInterval(100);
            setState(Idle); // Switch to idle when movement finishes
            setText("{P}");
        }
    });

    connect(animationTimer, &QTimer::timeout, this, &ProtagonistViewText::checkHealthPackCollision);

    poisonTimer->setInterval(500);
    poisonTimer->setSingleShot(true);
}

void ProtagonistViewText::onPositionChanged(int x, int y) {
    // Switch to walking state
    setState(Walking);

    // Stop any ongoing movement animation and update animation timer
    movementAnimation->stop();
    animationTimer->setInterval(60);

    // Set the animation start (current position) and end (target position)
    movementAnimation->setStartValue(pos());                                                                // Current position
    movementAnimation->setEndValue(QPoint(tileWidth * x + tileWidth / 4, tileHeight * y + tileHeight / 2)); // Target position

    // Start the movement animation and timer
    movementAnimation->start();

    /// Smoothly center the view on the protagonist
    if (scene() && !scene()->views().isEmpty()) {
        QGraphicsView *view = scene()->views().first(); // Get the first associated view
        if (view) {
            // Get the zoom scale factor of the view
            qreal zoomScale = view->transform().m11(); // Assuming uniform scaling

            // Target protagonist's position in the scene
            QPointF targetPosInScene = QPointF(tileWidth * x + tileWidth / 4, tileHeight * y + tileHeight / 2); // Target position

            // Calculate the center of the viewport in scene coordinates
            QPointF viewCenter = view->mapToScene(view->viewport()->rect().center());

            // Calculate scroll offsets adjusted for zoom
            int dx = (targetPosInScene.x() - viewCenter.x()) * zoomScale;
            int dy = (targetPosInScene.y() - viewCenter.y()) * zoomScale;

            // Calculate target scroll bar values
            int horizontalTarget = view->horizontalScrollBar()->value() + dx;
            int verticalTarget = view->verticalScrollBar()->value() + dy;

            // Create animations for vertical and horizontal scroll bars
            QPropertyAnimation *scrollAnimation = new QPropertyAnimation(view->verticalScrollBar(), "value", this);
            QPropertyAnimation *horizontalScrollAnimation = new QPropertyAnimation(view->horizontalScrollBar(), "value", this);

            // Set up vertical scroll animation
            scrollAnimation->setDuration(460); // Duration in milliseconds
            scrollAnimation->setStartValue(view->verticalScrollBar()->value());
            scrollAnimation->setEndValue(verticalTarget);
            scrollAnimation->setEasingCurve(QEasingCurve::Linear);

            // Set up horizontal scroll animation
            horizontalScrollAnimation->setDuration(460); // Duration in milliseconds
            horizontalScrollAnimation->setStartValue(view->horizontalScrollBar()->value());
            horizontalScrollAnimation->setEndValue(horizontalTarget);
            horizontalScrollAnimation->setEasingCurve(QEasingCurve::Linear);

            // Start animations
            scrollAnimation->start(QPropertyAnimation::DeleteWhenStopped);
            horizontalScrollAnimation->start(QPropertyAnimation::DeleteWhenStopped);
        }
    }
}

void ProtagonistViewText::onHealthChanged(int health) {
    if (health == 100) {
        // Add healing animation
        setText("+P+");
    }
    else if (health <= 0 && currentState != Dying) {
        setState(Dying);
    }
}

void ProtagonistViewText::onEnergyChanged(int energy) {
    // Switch to dying state if energy reaches 0
    if (energy <= 0 && currentState != Dying) {
        setState(Dying);
    }
}

void ProtagonistViewText::onDirectionChanged(Player::Direction dir) {
    currentDirection = dir;
}

void ProtagonistViewText::setAnimation() {
    QString figting;
    switch (currentState) {
    case Idle:
        font.setItalic(false);
        setFont(font);
        setText("{P}");
        currentFrameIndex = (currentFrameIndex + 1) % 16;
        if (currentFrameIndex < 8) {
            if (poisonTimer->isActive()) {
                // 0 - 128
                this->pen.setColor(QColor(216, 145, 239, 256 - 16 * currentFrameIndex));
            } else {
                this->pen.setColor((QColor(255 - 16 * currentFrameIndex, 255 - 16 * currentFrameIndex, 0)));
            }
            this->pen.setWidthF(1 + (2 - currentFrameIndex / 4.0));
            setPen(this->pen);

        } else {
            // 128 - 256
            this->pen.setColor((QColor(127 + 16 * (currentFrameIndex - 8), 127 + 16 * (currentFrameIndex - 8), 0)));
            this->pen.setWidthF((currentFrameIndex - 8) / 4.0);
            setPen(this->pen);
        }
        update();

        // Cycle through idle frames
        break;
    case Walking:
        // Cycle through walking frames
        font.setItalic(true);
        setFont(font);
        // Keep the same animation as idle
        currentFrameIndex = (currentFrameIndex + 1) % 16;
        if (currentFrameIndex < 8) {
            this->pen.setColor((QColor(255 - 16 * currentFrameIndex, 255 - 16 * currentFrameIndex, 0)));
            this->pen.setWidth(1 + (2 - currentFrameIndex / 4));
            setPen(this->pen);

        } else {
            this->pen.setColor((QColor(127 + 16 * (currentFrameIndex - 8), 127 + 16 * (currentFrameIndex - 8), 0)));
            this->pen.setWidth((currentFrameIndex - 8) / 4);
            setPen(this->pen);
        }
        update();
        break;
    case Fighting:
        // Play fighting frames once
        if (currentFrameIndex % 2)
            figting.append("~");
        else
            figting.append("-");

        figting.append("P");

        if (currentFrameIndex < 4)
            figting.append("/");
        else if (currentFrameIndex < 8)
            figting.append("_");
        else if (currentFrameIndex < 12)
            figting.append("}");
        else
            setState(Idle);

        setText(figting);

        /*currentFrameIndex = (currentFrameIndex + 1) % 16;*/
        if (currentFrameIndex < 8) {
            this->pen.setColor((QColor(255 - 32 * currentFrameIndex, 0, 0)));
            this->pen.setWidth((2 - currentFrameIndex / 4));
            setPen(this->pen);

        } else {
            this->pen.setColor((QColor(32 * (currentFrameIndex - 8), 0, 0)));
            this->pen.setWidth((currentFrameIndex - 8) / 4);
            setPen(this->pen);
        }
        update();
        break;
    case Dying:
        // Play dying frames once
        setText("_X_");
        break;
    }
}

void ProtagonistViewText::checkHealthPackCollision() {
    // Get a list of all items the protagonist is colliding with
    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems) {
        // Check if the item is a HealthPackView2D
        HealthPackViewText *healthPack = dynamic_cast<HealthPackViewText *>(item);
        if (healthPack) {
            // Trigger the health pack animation
            healthPack->playPickupAnimation();
            break;
        }
    }
}

void ProtagonistViewText::onPlayerAttack() {
    setState(Fighting);
}

void ProtagonistViewText::setPoisonEffect() {
    poisonTimer->start();
}
