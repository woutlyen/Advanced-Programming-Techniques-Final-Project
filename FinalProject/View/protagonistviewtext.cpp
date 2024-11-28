#include "protagonistviewtext.h"

ProtagonistViewText::ProtagonistViewText(const std::unique_ptr<Protagonist> &protagonist, double tileWidth, double tileHeight, QFont font, QGraphicsItem *parent)
    : QObject(),
      QGraphicsSimpleTextItem(parent),
      currentState{Idle},
      movementAnimation(new QPropertyAnimation(this, "pos")),
      animationTimer(new QTimer(this)),
      currentFrameIndex{0} {

    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->font = font;

    // Set the initial pixmap
    setText(QString("P"));
    setFont(font);
    setPos(tileWidth * protagonist->getXPos() + tileWidth / 2, tileHeight * protagonist->getYPos() + tileHeight / 2);

    // Connect signalsc & slots
    connect(protagonist.get(), &Protagonist::posChanged, this, &ProtagonistViewText::onPositionChanged);
    connect(protagonist.get(), &Protagonist::healthChanged, this, &ProtagonistViewText::onHealthChanged);
    connect(protagonist.get(), &Protagonist::energyChanged, this, &ProtagonistViewText::onEnergyChanged);

    // Configure the movement animation
    movementAnimation->setDuration(480); // Animation duration (in milliseconds)
    movementAnimation->setEasingCurve(QEasingCurve::Linear);

    // Configure the animation timer
    animationTimer->setInterval(400); // Frame switch interval (in milliseconds)
    animationTimer->start();
    connect(animationTimer, &QTimer::timeout, this, &ProtagonistViewText::updateAnimationFrame);
    connect(movementAnimation, &QPropertyAnimation::finished, this, [this]() {
        if (currentState == Walking) {
            animationTimer->setInterval(400);
            setState(Idle); // Switch to idle when movement finishes
        }
    });
}

void ProtagonistViewText::onPositionChanged(int x, int y) {
    // Switch to walking state
    setState(Walking);

    // Stop any ongoing movement animation and update animation timer
    movementAnimation->stop();
    animationTimer->setInterval(60);

    // Set the animation start (current position) and end (target position)
    movementAnimation->setStartValue(pos());                                                               // Current position
    movementAnimation->setEndValue(QPoint(tileWidth * x + tileWidth / 2, tileHeight * y + tileWidth / 2)); // Target position

    // Start the movement animation and timer
    movementAnimation->start();
}

void ProtagonistViewText::onHealthChanged(int health) {
    // Switch to fighting state
    setState(Fighting);
}

void ProtagonistViewText::onEnergyChanged(int energy) {
    // Switch to dying state if energy reaches 0
    if (energy <= 0 && currentState != Dying) {
        setState(Dying);
    }
}

void ProtagonistViewText::setState(AnimationState newState) {
    if (currentState == newState or currentState == Dying)
        return; // No state change
    currentState = newState;

    // Reset frame index for the new state
    currentFrameIndex = 0;

    // Update the pixmap for the new state
    switch (currentState) {
    case Idle:
        break;
    case Walking:
        break;
    case Fighting:
        break;
    case Dying:
        break;
    }
}

void ProtagonistViewText::updateAnimationFrame() {
    switch (currentState) {
    case Idle:
        // Cycle through idle frames
        setText((text().isUpper()) ? QString("p") : QString("P"));
        this->font.setItalic(false);
        setFont(this->font);
        break;
    case Walking:
        // Cycle through walking frames
        (this->font.italic()) ? this->font.setItalic(false) : this->font.setItalic(true);
        setFont(this->font);
        break;
    case Fighting:
        // Play fighting frames once
        break;
    case Dying:
        // Play dying frames once
        break;
    }
}
