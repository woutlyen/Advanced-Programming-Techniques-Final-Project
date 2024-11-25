#include "protagonistview2d.h"

ProtagonistView2D::ProtagonistView2D(const std::unique_ptr<Protagonist>& protagonist, std::size_t gridSize, QGraphicsItem* parent)
    : QObject(),
    QGraphicsPixmapItem(parent),
    currentState{Fighting},
    movementAnimation(new QPropertyAnimation(this, "pos")),
    animationTimer(new QTimer(this)),
    currentFrameIndex{0}
    {

    this->gridSize = gridSize;
    idlePixmaps = extractFrames(":/images/IDLE.png", 40, 40, 7);
    walkingPixmaps = extractFrames(":/images/WALK.png", 40, 40, 8);
    fightingPixmaps = extractFrames(":/images/ATTACK1.png", 56, 40, 6);
    dyingPixmaps = extractFrames(":/images/DEATH.png", 56, 40, 12);

    // Set the initial pixmap
    setPixmap(idlePixmaps[0]);
    setPos(gridSize*protagonist->getXPos(), gridSize*protagonist->getYPos());

    // Connect signalsc & slots
    connect(protagonist.get(), &Protagonist::posChanged, this, &ProtagonistView2D::onPositionChanged);
    //connect(protagonist.get(), &Protagonist::healthChanged, this, &ProtagonistView2D::onHealthChanged);
    connect(protagonist.get(), &Protagonist::energyChanged, this, &ProtagonistView2D::onEnergyChanged);

    // Configure the movement animation
    movementAnimation->setDuration(640); // Animation duration (in milliseconds)
    movementAnimation->setEasingCurve(QEasingCurve::Linear);

    // Configure the animation timer
    animationTimer->setInterval(80); // Frame switch interval (in milliseconds)
    animationTimer->start();
    connect(animationTimer, &QTimer::timeout, this, &ProtagonistView2D::updateAnimationFrame);
    connect(movementAnimation, &QPropertyAnimation::finished, this, [this]() {
        if (currentState == Walking) {
            setState(Idle); // Switch to idle when movement finishes
        }
    });
}

void ProtagonistView2D::onPositionChanged(int x, int y)
{
    // Switch to walking state
    setState(Walking);

    // Stop any ongoing movement animation and animation timer
    movementAnimation->stop();

    // Set the animation start (current position) and end (target position)
    movementAnimation->setStartValue(pos()); // Current position
    movementAnimation->setEndValue(QPoint(gridSize * x, gridSize * y)); // Target position

    // Start the movement animation and timer
    movementAnimation->start();
}

void ProtagonistView2D::onEnergyChanged(int energy)
{
    // Switch to dying state if energy reaches 0
    if (energy <= 0 && currentState != Dying) {
        setState(Dying);
    }
}

void ProtagonistView2D::setState(AnimationState newState) {
    if (currentState == newState or currentState == Dying) return; // No state change
    currentState = newState;

    // Reset frame index for the new state
    currentFrameIndex = 0;

    // Update the pixmap for the new state
    switch (currentState) {
    case Idle:
        setPixmap(idlePixmaps[currentFrameIndex]);
        break;
    case Walking:
        setPixmap(walkingPixmaps[currentFrameIndex]);
        break;
    case Fighting:
        setPixmap(fightingPixmaps[currentFrameIndex]);
        break;
    case Dying:
        setPixmap(dyingPixmaps[currentFrameIndex]);
        break;
    }
}

void ProtagonistView2D::updateAnimationFrame() {
    switch (currentState) {
    case Idle:
        // Cycle through idle frames
        currentFrameIndex = (currentFrameIndex + 1) % idlePixmaps.size();
        setPixmap(idlePixmaps[currentFrameIndex]);
        break;
    case Walking:
        // Cycle through walking frames
        currentFrameIndex = (currentFrameIndex + 1) % walkingPixmaps.size();
        setPixmap(walkingPixmaps[currentFrameIndex]);
        break;
    case Fighting:
        // Play dying frames once
        currentFrameIndex = (currentFrameIndex + 1) % fightingPixmaps.size();
        setPixmap(fightingPixmaps[currentFrameIndex]);
        break;
    case Dying:
        // Play dying frames once
        if (currentFrameIndex < dyingPixmaps.size() - 1) {
            currentFrameIndex++;
            setPixmap(dyingPixmaps[currentFrameIndex]);
        } else {
            animationTimer->stop(); // Stop the timer when animation ends
        }
        break;
    }
}

std::vector<QPixmap> ProtagonistView2D::extractFrames(const QString& filePath, int frameWidth, int frameHeight, int numberOfFrames) {
    std::vector<QPixmap> frames;

    // Load the full spritesheet
    QPixmap spriteSheet(filePath);

    // Extract each frame
    for (int i = 0; i < numberOfFrames; ++i) {
        QPixmap frame = spriteSheet.copy(i * spriteSheet.width()/numberOfFrames + ((spriteSheet.width()/numberOfFrames)-frameWidth)/2, (spriteSheet.height()-frameHeight)/2, frameWidth, frameHeight);
        frames.push_back(frame.scaledToHeight(gridSize));
    }

    return frames;
}
