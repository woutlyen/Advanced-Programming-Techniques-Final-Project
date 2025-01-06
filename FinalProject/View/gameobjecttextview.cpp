#include "gameobjecttextview.h"

GameObjectTextView::GameObjectTextView(double tileWidth, double tileHeight, QFont font, QGraphicsItem *parent)
    : QObject(),
      QGraphicsSimpleTextItem(parent),
      currentFrameIndex{0},
      tileWidth{tileWidth},
      tileHeight{tileHeight},
      animationTimer{new QTimer(this)},
      font{font} {
    setFont(font);
}

void GameObjectTextView::setState(AnimationState newState) {
    if (currentState == newState or currentState == Dying) return; // No state change
    currentState = newState;
    // Reset frame index for the new state
    currentFrameIndex = 0;

    // Update the pixmap for the new state
    setAnimation();
}

void GameObjectTextView::updateAnimationFrame() {
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

void GameObjectTextView::updateCurrentFrameIndex()
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

void GameObjectTextView::connectAnimationTimer()
{
    connect(animationTimer, &QTimer::timeout, this, &GameObjectTextView::updateAnimationFrame);
}

