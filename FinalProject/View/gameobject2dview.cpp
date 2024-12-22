#include "gameobject2dview.h"

GameObject2DView::GameObject2DView(std::size_t gridSize, QGraphicsItem *parent):QObject(), QGraphicsPixmapItem(parent),currentState{AnimationState::Idle}, currentFrameIndex{0}, gridSize{gridSize}, animationTimer(new QTimer(this))
 {}

void GameObject2DView::setState(AnimationState newState) {
    if (currentState == newState or currentState == Dying) return; // No state change
    currentState = newState;
    // Reset frame index for the new state
    currentFrameIndex = 0;

    // Update the pixmap for the new state
    setAnimation();
}

void GameObject2DView::updateAnimationFrame() {
    switch (currentState) {
    case Idle:
        // Cycle through idle frames,
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
        if (currentFrameIndex < getNrOfFramesFighting() - 1) {
            updateCurrentFrameIndex();
            setAnimation();
        } else {
            setState(Idle);
        }
        break;
    case Dying:
        // Play dying frames once
        if (currentFrameIndex < getNrOfFramesDying() - 1) {
            updateCurrentFrameIndex();
            setAnimation();
        } else {
            animationTimer->stop(); // Stop the timer when animation ends
        }
        break;
    }
}

void GameObject2DView::updateCurrentFrameIndex()
{
    switch (currentState) {
    case Idle:
        currentFrameIndex = (currentFrameIndex + 1) % getNrOfFramesIdle();
        break;
    case Walking:
        currentFrameIndex = (currentFrameIndex + 1) % getNrOfFramesWalking();
        break;
    case Fighting:
        currentFrameIndex++;
        break;
    case Dying:
        currentFrameIndex++;
        break;
    }
}

void GameObject2DView::connectAnimationTimer()
{
    connect(animationTimer, &QTimer::timeout, this, &GameObject2DView::updateAnimationFrame);
}

std::vector<QPixmap> GameObject2DView::extractFrames(const QString &fileDir) {
    std::vector<QPixmap> frames;
    QPixmap frame;

    QDirIterator it(fileDir, QDirIterator::NoIteratorFlags);
    while (it.hasNext()){
        frame = it.next();
        frames.push_back(frame.scaledToHeight(gridSize));
    }
    return frames;
}

std::vector<QPixmap> GameObject2DView::extractFramesFromSpritesheet(const QString& filePath, int frameWidth, int frameHeight, int numberOfFrames) {
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
