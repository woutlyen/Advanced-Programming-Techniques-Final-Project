#include "protagonistview2d.h"
#include "View/healthpackview2d.h"

#include <QGraphicsColorizeEffect>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QScrollBar>

ProtagonistView2D::ProtagonistView2D(const std::unique_ptr<Player> &protagonist, std::size_t gridSize)
    : GameObject2DView(gridSize),
    movementAnimation(new QPropertyAnimation(this, "pos"))
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

    currentDirection = Player::Front,


    // Set the initial pixmap
    setPixmap(idlePixmaps_front[0]);
    setPos(gridSize*protagonist->getXPos(), gridSize*protagonist->getYPos());

    // Connect signalsc & slots
    connect(protagonist.get(), &Player::posChanged, this, &ProtagonistView2D::onPositionChanged);
    connect(protagonist.get(), &Player::healthChanged, this, &ProtagonistView2D::onHealthChanged);
    connect(protagonist.get(), &Player::energyChanged, this, &ProtagonistView2D::onEnergyChanged);
    connect(protagonist.get(), &Player::directionChanged, this, &ProtagonistView2D::onDirectionChanged);
    connect(protagonist.get(), &Player::poisoned, this, &ProtagonistView2D::setPoisonEffect);


    // Configure the movement animation
    movementAnimation->setDuration(480); // Animation duration (in milliseconds)
    movementAnimation->setEasingCurve(QEasingCurve::Linear);

    // Configure the animation timer
    animationTimer->setInterval(120); // Frame switch interval (in milliseconds)
    animationTimer->start();
    connectAnimationTimer();
    connect(movementAnimation, &QPropertyAnimation::finished, this, [this]() {
        if (currentState == Walking) {
            animationTimer->setInterval(120);

            setState(Idle); // Switch to idle when movement finishes
        }
    });

    // check for healthpackcollisions
    connect(animationTimer, &QTimer::timeout, this, &ProtagonistView2D::checkHealthPackCollision);

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

    else{
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

void ProtagonistView2D::onDirectionChanged(Player::Direction dir)
{
    currentDirection = dir;
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

            // Trigger the healing glow effect on the player
            setHealingGlow();
            break;
        }
    }
}

void ProtagonistView2D::setHealingGlow(){
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

void ProtagonistView2D::removeAllEffects()
{
    setGraphicsEffect(nullptr);
}

void ProtagonistView2D::setPoisonEffect()
{
    QGraphicsColorizeEffect* poisonEffect = new QGraphicsColorizeEffect(this);
    poisonEffect->setColor(QColor(83, 0, 128));
    poisonEffect->setStrength(0.0);
    setGraphicsEffect(poisonEffect);

    QPropertyAnimation* poisonAnimation = new QPropertyAnimation(poisonEffect, "strength", this);
    poisonAnimation->setDuration(500);
    poisonAnimation->setStartValue(0.0);
    poisonAnimation->setEndValue(1.0);
    poisonAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    poisonAnimation->setLoopCount(5);

    poisonAnimation->start(QPropertyAnimation::DeleteWhenStopped);
}
