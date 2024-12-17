#ifndef GAMEOBJECT2DVIEW_H
#define GAMEOBJECT2DVIEW_H

#include <QGraphicsPixmapItem>

class GameObject2DView : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameObject2DView(std::size_t gridSize, QGraphicsItem* parent = nullptr);

protected:
    enum AnimationState { Idle, Walking, Fighting, Dying }; // Animation states
    AnimationState currentState;                 // Current animation state
    int currentFrameIndex;                 // Current frame index in pixmap arrays
    int nrOfFramesIdle;
    int nrOfFramesWalking;
    int nrOfFramesFighting;
    int nrOfFramesDying;
    std::size_t gridSize{};
    QTimer* animationTimer;                // Timer for cycling pixmaps
    void setState(AnimationState newState); // Switch animation state
    std::vector<QPixmap> extractFramesFromSpritesheet(const QString &filePath, int frameWidth, int frameHeight, int numberOfFrames);
    std::vector<QPixmap> extractFrames(const QString &fileDir);
    void updateCurrentFrameIndex();
    virtual void setAnimation() = 0;
    void connectAnimationTimer();

protected slots:
    void updateAnimationFrame(); // Update animation frame


};

#endif // GAMEOBJECT2DVIEW_H
