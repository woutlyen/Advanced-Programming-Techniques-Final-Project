#ifndef GAMEOBJECTTEXTVIEW_H
#define GAMEOBJECTTEXTVIEW_H

#include <QDir>
#include <QDirIterator>
#include <QFont>
#include <QGraphicsSimpleTextItem>
#include <QPen>
#include <QPropertyAnimation>
#include <QTimer>

class GameObjectTextView : public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT
  public:
    GameObjectTextView(double tileWidth, double tileHeight, QFont font, QGraphicsItem *parent = nullptr);
    virtual int getNrOfFramesIdle() const = 0;
    virtual int getNrOfFramesWalking() const = 0;
    virtual int getNrOfFramesFighting() const = 0;
    virtual int getNrOfFramesDying() const = 0;

  protected:
    enum AnimationState { Idle,
                          Walking,
                          Fighting,
                          Dying }; // Animation states
    AnimationState currentState;   // Current animation state
    int currentFrameIndex;         // Current frame index in pixmap arrays
    double tileWidth, tileHeight;
    QTimer *animationTimer; // Timer for cycling pixmaps
    QPen pen;
    QFont font;
    void setState(AnimationState newState); // Switch animation state
    void updateCurrentFrameIndex();
    void connectAnimationTimer();
    virtual void setAnimation() = 0;

  protected slots:
    void updateAnimationFrame(); // Update animation frame
};

#endif // GAMEOBJECT2DVIEW_H
