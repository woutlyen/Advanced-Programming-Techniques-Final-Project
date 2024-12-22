#ifndef PROTAGONISTVIEW2D_H
#define PROTAGONISTVIEW2D_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>
#include <QDir>
#include <QDirIterator>
#include "Model/player.h"

class ProtagonistView2D : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos) // Ensure Q_PROPERTY for pos is declared

public:
    ProtagonistView2D(const std::unique_ptr<Player>& protagonist, std::size_t gridSize, QGraphicsItem* parent = nullptr);

private:
    std::size_t gridSize{};
    enum AnimationState { Idle, Walking, Fighting, Dying }; // Animation states
    AnimationState currentState;                 // Current animation state
    Player::Direction currentDirection;
    void updateDirection(Player::Direction);
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
    void updateCurrentFrameIndex();
    void setAnimation();
    void checkHealthPackCollision();

private slots:
    void onPositionChanged(int x, int y); // Updates the protagonist's position
    void onHealthChanged(int health);    // Updates the protagonist's visual representation
    void onEnergyChanged(int energy);    // Updates the protagonist's visual representation
    void updateAnimationFrame(); // Update animation frame
    void onDirectionChanged(Player::Direction dir);

};

#endif // PROTAGONISTVIEW2D_H
