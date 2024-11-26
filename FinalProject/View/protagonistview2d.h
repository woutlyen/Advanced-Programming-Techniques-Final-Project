#ifndef PROTAGONISTVIEW2D_H
#define PROTAGONISTVIEW2D_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>
#include <QDir>
#include <QDirIterator>
#include "world.h"


class ProtagonistView2D : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos) // Ensure Q_PROPERTY for pos is declared

public:
    ProtagonistView2D(const std::unique_ptr<Protagonist>& protagonist, std::size_t gridSize, QGraphicsItem* parent = nullptr);

private:
    std::size_t gridSize{};
    enum Direction {Front, Back, Left, Right};
    enum AnimationState { Idle, Walking, Fighting, Dying }; // Animation states
    AnimationState currentState;                 // Current animation state
    Direction currentDirection;

    QPropertyAnimation* movementAnimation; // Animation for position movement
    QTimer* animationTimer;                // Timer for cycling pixmaps
    // Pixmaps for idle animation
    std::vector<QPixmap> idlePixmaps_front;
    std::vector<QPixmap> idlePixmaps_left;
    std::vector<QPixmap> idlePixmaps_right;
    std::vector<QPixmap> idlePixmaps_back;
    // Pixmaps for walking animation
    std::vector<QPixmap> walkingPixmaps_front;
    std::vector<QPixmap> walkingPixmaps_left;
    std::vector<QPixmap> walkingPixmaps_right;
    std::vector<QPixmap> walkingPixmaps_back;
    // Pixmaps for fighting animation
    std::vector<QPixmap> fightingPixmaps_front;
    std::vector<QPixmap> fightingPixmaps_left;
    std::vector<QPixmap> fightingPixmaps_right;
    std::vector<QPixmap> fightingPixmaps_back;
    // Pixmaps for dying animation
    std::vector<QPixmap> dyingPixmaps;
    int currentFrameIndex;                 // Current frame index in pixmap arrays

    void setState(AnimationState newState); // Switch animation state
    std::vector<QPixmap> extractFramesFromSpritesheet(const QString &filePath, int frameWidth, int frameHeight, int numberOfFrames);
    std::vector<QPixmap> extractFrames(const QString &fileDir);
    void updateDirection(int curX, int curY, int newX, int newY);

private slots:
    void onPositionChanged(int x, int y); // Updates the protagonist's position
    void onHealthChanged(int health);    // Updates the protagonist's visual representation
    void onEnergyChanged(int energy);    // Updates the protagonist's visual representation
    void updateAnimationFrame(); // Update animation frame
};

#endif // PROTAGONISTVIEW2D_H
