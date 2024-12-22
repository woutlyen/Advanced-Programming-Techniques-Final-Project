#include "protagonistview2d.h"
#include "View/healthpackview2d.h"

#include <QGraphicsColorizeEffect>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QScrollBar>

ProtagonistView2D::ProtagonistView2D(const std::unique_ptr<Player> &protagonist, std::size_t gridSize, QGraphicsItem* parent)
    : QObject(),
    QGraphicsPixmapItem(parent),
    gridSize{gridSize},
    currentState{Idle},
    currentDirection{Player::Front},
    movementAnimation(new QPropertyAnimation(this, "pos")),
    animationTimer(new QTimer(this)),
    currentFrameIndex{0}
    {

    // Initialize all Pixmaps
    idlePixmaps_front = extractFrames(":/images/player_sprites/player_idle_front");
    idlePixmaps_left = extractFrames(":/images/player_sprites/player_idle_left");
    idlePixmaps_right = extractFrames(":/images/player_sprites/player_idle_right");
    idlePixmaps_back = extractFrames(":/images/player_sprites/player_idle_back");

    walkingPixmaps_front = extractFrames(":/images/player_sprites/player_walk_front");
    walkingPixmaps_left = extractFrames(":/images/player_sprites/player_walk_left");
    walkingPixmaps_right = extractFrames(":/images/player_sprites/player_walk_right");
    walkingPixmaps_back = extractFrames(":/images/player_sprites/player_walk_back");

    fightingPixmaps_front = extractFrames(":/images/player_sprites/player_attack_front");
    fightingPixmaps_left = extractFrames(":/images/player_sprites/player_attack_left");
    fightingPixmaps_right = extractFrames(":/images/player_sprites/player_attack_right");
    fightingPixmaps_back = extractFrames(":/images/player_sprites/player_attack_back");

    dyingPixmaps = extractFrames(":/images/player_sprites/player_die");

    // Set the initial pixmap
    setPixmap(idlePixmaps_front[0]);
    setPos(gridSize*protagonist->getXPos(), gridSize*protagonist->getYPos());

    // Connect signalsc & slots
    connect(protagonist.get(), &Player::posChanged, this, &ProtagonistView2D::onPositionChanged);
    connect(protagonist.get(), &Player::healthChanged, this, &ProtagonistView2D::onHealthChanged);
    connect(protagonist.get(), &Player::energyChanged, this, &ProtagonistView2D::onEnergyChanged);
    connect(protagonist.get(), &Player::directionChanged, this, &ProtagonistView2D::onDirectionChanged);

    // Configure the movement animation
    movementAnimation->setDuration(480); // Animation duration (in milliseconds)
    movementAnimation->setEasingCurve(QEasingCurve::Linear);

    // Configure the animation timer
    animationTimer->setInterval(120); // Frame switch interval (in milliseconds)
    animationTimer->start();
    connect(animationTimer, &QTimer::timeout, this, &ProtagonistView2D::updateAnimationFrame);
    connect(movementAnimation, &QPropertyAnimation::finished, this, [this]() {
        if (currentState == Walking) {
            animationTimer->setInterval(120);

            setState(Idle); // Switch to idle when movement finishes
        }
    });
}

void ProtagonistView2D::onPositionChanged(int x, int y)
{
    // Switch to walking state
    setState(Walking);

    // Stop any ongoing movement animation and update animation timer
    movementAnimation->stop();
    // Set the animation start (current position) and end (target position)
    movementAnimation->setStartValue(pos()); // Current position
    movementAnimation->setEndValue(QPoint(gridSize * x, gridSize * y)); // Target position

    // Start the movement animation and timer
    movementAnimation->start();

    /// Smoothly center the view on the protagonist
    if (scene() && !scene()->views().isEmpty()) {
        QGraphicsView* view = scene()->views().first(); // Get the first associated view
        if (view) {
            // Get the zoom scale factor of the view
            qreal zoomScale = view->transform().m11(); // Assuming uniform scaling

            // Target protagonist's position in the scene
            QPointF targetPosInScene = QPointF(gridSize * x + gridSize/2, gridSize * y + gridSize/2); // Target position

            // Calculate the center of the viewport in scene coordinates
            QPointF viewCenter = view->mapToScene(view->viewport()->rect().center());

            // Calculate scroll offsets adjusted for zoom
            int dx = (targetPosInScene.x() - viewCenter.x()) * zoomScale;
            int dy = (targetPosInScene.y() - viewCenter.y()) * zoomScale;

            // Calculate target scroll bar values
            int horizontalTarget = view->horizontalScrollBar()->value() + dx;
            int verticalTarget = view->verticalScrollBar()->value() + dy;

            // Create animations for vertical and horizontal scroll bars
            QPropertyAnimation* scrollAnimation = new QPropertyAnimation(view->verticalScrollBar(), "value", this);
            QPropertyAnimation* horizontalScrollAnimation = new QPropertyAnimation(view->horizontalScrollBar(), "value", this);

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

void ProtagonistView2D::onHealthChanged(int health)
{
    if (health == 100){
        // Add a glow effect
        QGraphicsColorizeEffect* glowEffect = new QGraphicsColorizeEffect(this);
        glowEffect->setColor(Qt::darkRed); // Green indicates healing
        glowEffect->setStrength(0.0);    // Start with no glow
        setGraphicsEffect(glowEffect);

        // Animate the glow effect
        QPropertyAnimation* glowAnimation = new QPropertyAnimation(glowEffect, "strength", this);
        glowAnimation->setDuration(500); // Half a second
        glowAnimation->setStartValue(0.0);
        glowAnimation->setKeyValueAt(0.5, 1.0); // Peak glow in the middle
        glowAnimation->setEndValue(0.0);        // Fade back to normal
        glowAnimation->start(QPropertyAnimation::DeleteWhenStopped);
    }
    else {
        // Switch to fighting state
        setState(Fighting);
    }

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
    setAnimation();
}

void ProtagonistView2D::updateAnimationFrame() {
    switch (currentState) {
    case Idle:
        // Cycle through idle frames
        updateCurrentFrameIndex();
        setAnimation();
        break;
    case Walking:
        // Cycle through walking frames
        updateCurrentFrameIndex();
        setAnimation();
        break;
    case Fighting:
        // Play fighting frames once
        if (currentFrameIndex < fightingPixmaps_front.size() - 1) {
            updateCurrentFrameIndex();
            setAnimation();
        } else {
            setState(Idle);
        }
        break;
    case Dying:
        // Play dying frames once
        if (currentFrameIndex < dyingPixmaps.size() - 1) {
           updateCurrentFrameIndex();
            setAnimation();
        } else {
            animationTimer->stop(); // Stop the timer when animation ends
        }
        break;
    }

    // Check for health pack collisions
    checkHealthPackCollision();
}

void ProtagonistView2D::onDirectionChanged(Player::Direction dir)
{
    currentDirection = dir;
    qDebug() << "new direction is: " << currentDirection;
}

void ProtagonistView2D::updateCurrentFrameIndex()
{
    switch (currentState) {
    case Idle:
        currentFrameIndex = (currentFrameIndex + 1) % idlePixmaps_front.size();
        break;
    case Walking:
        currentFrameIndex = (currentFrameIndex + 1) % walkingPixmaps_front.size();
        break;
    case Fighting:
        currentFrameIndex++;
        break;
    case Dying:
        currentFrameIndex++;
        break;
    }
}

void ProtagonistView2D::setAnimation()
{
    switch (currentState) {
    case Idle:
        animationTimer->setInterval(180);
        switch(currentDirection){
        case Player::Front:
            setPixmap(idlePixmaps_front[currentFrameIndex]);
            break;
        case Player::Back:
            setPixmap(idlePixmaps_back[currentFrameIndex]);
            break;
        case Player::Left:
            setPixmap(idlePixmaps_left[currentFrameIndex]);
            break;
        case Player::Right:
            setPixmap(idlePixmaps_right[currentFrameIndex]);
            break;
        }

        break;
    case Walking:
        animationTimer->setInterval(90);
        switch(currentDirection){
        case Player::Front:
            setPixmap(walkingPixmaps_front[currentFrameIndex]);
            break;
        case Player::Back:
            setPixmap(walkingPixmaps_back[currentFrameIndex]);
            break;
        case Player::Left:
            setPixmap(walkingPixmaps_left[currentFrameIndex]);
            break;
        case Player::Right:
            setPixmap(walkingPixmaps_right[currentFrameIndex]);
            break;
        }
        break;

    case Fighting:
        animationTimer->setInterval(120);
        switch(currentDirection){
        case Player::Front:
            setPixmap(fightingPixmaps_front[currentFrameIndex]);
            break;
        case Player::Back:
            setPixmap(fightingPixmaps_back[currentFrameIndex]);
            break;
        case Player::Left:
            setPixmap(fightingPixmaps_left[currentFrameIndex]);
            break;
        case Player::Right:
            setPixmap(fightingPixmaps_right[currentFrameIndex]);
            break;
        }
        break;
    case Dying:
        setPixmap(dyingPixmaps[currentFrameIndex]);
        break;
    }
}


std::vector<QPixmap> ProtagonistView2D::extractFrames(const QString &fileDir) {
    std::vector<QPixmap> frames;
    QPixmap frame;

    QDirIterator it(fileDir, QDirIterator::NoIteratorFlags);
    while (it.hasNext()){
        frame = it.next();
        frames.push_back(frame.scaledToHeight(gridSize));
    }
    return frames;
}

std::vector<QPixmap> ProtagonistView2D::extractFramesFromSpritesheet(const QString& filePath, int frameWidth, int frameHeight, int numberOfFrames) {
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

void ProtagonistView2D::checkHealthPackCollision()
{
    // Get a list of all items the protagonist is colliding with
    QList<QGraphicsItem*> collidingItems = scene()->collidingItems(this);

    for (QGraphicsItem* item : collidingItems) {
        // Check if the item is a HealthPackView2D
        HealthPackView2D* healthPack = dynamic_cast<HealthPackView2D*>(item);
        if (healthPack) {
            // Trigger the health pack animation
            healthPack->playPickupAnimation();
            break;
        }
    }
}
