#ifndef PROTAGONISTVIEW2D_H
#define PROTAGONISTVIEW2D_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>
#include "world.h"


class ProtagonistView2D : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos) // Ensure Q_PROPERTY for pos is declared

public:
    ProtagonistView2D(const std::unique_ptr<Protagonist>& protagonist, std::size_t gridSize, QGraphicsItem* parent = nullptr);

private:
    std::size_t gridSize{};
    enum AnimationState { Idle, Walking, Fighting, Dying }; // Animation states
    AnimationState currentState;                 // Current animation state

    QPropertyAnimation* movementAnimation; // Animation for position movement
    QTimer* animationTimer;                // Timer for cycling pixmaps
    std::vector<QPixmap> idlePixmaps;          // Pixmaps for idle animation
    std::vector<QPixmap> walkingPixmaps;       // Pixmaps for walking animation
    std::vector<QPixmap> fightingPixmaps;       // Pixmaps for fighting animation
    std::vector<QPixmap> dyingPixmaps;         // Pixmaps for dying animation
    int currentFrameIndex;                 // Current frame index in pixmap arrays

    void setState(AnimationState newState); // Switch animation state
    std::vector<QPixmap> extractFrames(const QString& filePath, int frameWidth, int frameHeight, int numberOfFrames);

private slots:
    void onPositionChanged(int x, int y); // Updates the protagonist's position
    //void onHealthChanged(int health);    // Updates the protagonist's visual representation
    void onEnergyChanged(int energy);    // Updates the protagonist's visual representation
    void updateAnimationFrame(); // Update animation frame
};

#endif // PROTAGONISTVIEW2D_H
