#include "protagonistview2d.h"

ProtagonistView2D::ProtagonistView2D(const std::unique_ptr<Player> &protagonist, std::size_t gridSize, QGraphicsItem* parent)
    : QObject(),
    QGraphicsPixmapItem(parent),
    currentState{Idle},
    currentDirection{Front},
    movementAnimation(new QPropertyAnimation(this, "pos")),
    animationTimer(new QTimer(this)),
    currentFrameIndex{0}
    {

    this->gridSize = gridSize;

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
    connect(protagonist.get(), &Protagonist::posChanged, this, &ProtagonistView2D::onPositionChanged);
    connect(protagonist.get(), &Protagonist::healthChanged, this, &ProtagonistView2D::onHealthChanged);
    connect(protagonist.get(), &Protagonist::energyChanged, this, &ProtagonistView2D::onEnergyChanged);

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
    updateDirection(pos().x(), pos().y(), x, y);
    // Switch to walking state
    setState(Walking);

    // Stop any ongoing movement animation and update animation timer
    movementAnimation->stop();
    // Set the animation start (current position) and end (target position)
    movementAnimation->setStartValue(pos()); // Current position
    movementAnimation->setEndValue(QPoint(gridSize * x, gridSize * y)); // Target position

    // Start the movement animation and timer
    movementAnimation->start();
}

void ProtagonistView2D::onHealthChanged(int health)
{
    // Switch to fighting state
    setState(Fighting);
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
}

void ProtagonistView2D::updateDirection(int curX, int curY, int newX, int newY)
{

    if((curX > (newX * gridSize ))&& (curY == (newY * gridSize))){
        currentDirection = Left;
    }
    else if((curX < (newX * gridSize ))&& (curY == (newY * gridSize))){
        currentDirection = Right;
    }
    else if(curY > (newY * gridSize)){
        currentDirection = Back;
    }
    else{
        currentDirection = Front;
    }
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
        case Front:
            setPixmap(idlePixmaps_front[currentFrameIndex]);
            break;
        case Back:
            setPixmap(idlePixmaps_back[currentFrameIndex]);
            break;
        case Left:
            setPixmap(idlePixmaps_left[currentFrameIndex]);
            break;
        case Right:
            setPixmap(idlePixmaps_right[currentFrameIndex]);
            break;
        }

        break;
    case Walking:
        animationTimer->setInterval(90);
        switch(currentDirection){
        case Front:
            setPixmap(walkingPixmaps_front[currentFrameIndex]);
            break;
        case Back:
            setPixmap(walkingPixmaps_back[currentFrameIndex]);
            break;
        case Left:
            setPixmap(walkingPixmaps_left[currentFrameIndex]);
            break;
        case Right:
            setPixmap(walkingPixmaps_right[currentFrameIndex]);
            break;
        }
        break;

    case Fighting:
        animationTimer->setInterval(120);
        switch(currentDirection){
        case Front:
            setPixmap(fightingPixmaps_front[currentFrameIndex]);
            break;
        case Back:
            setPixmap(fightingPixmaps_back[currentFrameIndex]);
            break;
        case Left:
            setPixmap(fightingPixmaps_left[currentFrameIndex]);
            break;
        case Right:
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
