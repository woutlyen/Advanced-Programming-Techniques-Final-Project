#ifndef PROTAGONISTVIEW2D_H
#define PROTAGONISTVIEW2D_H

#include <QObject>
#include "Model/player.h"
#include "View/gameobject2dview.h"

class ProtagonistView2D : public GameObject2DView
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos) // Ensure Q_PROPERTY for pos is declared

public:
    ProtagonistView2D(const std::unique_ptr<Player>& protagonist, std::size_t gridSize);

private:
    Player::Direction currentDirection;
    void updateDirection(Player::Direction);

    int getNrOfFramesIdle() const override{ return idlePixmaps_front.size();}
    int getNrOfFramesWalking() const override{ return walkingPixmaps_front.size();}
    int getNrOfFramesFighting() const override{ return fightingPixmaps_front.size();}
    int getNrOfFramesDying() const override{ return dyingPixmaps.size();}

    QPropertyAnimation* movementAnimation; // Animation for position movement
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
    void setAnimation() override;
    void setHealingGlow();
    void removeAllEffects();

private slots:
    void onPositionChanged(int x, int y); // Updates the protagonist's position
    void onHealthChanged(int health);    // Updates the protagonist's visual representation
    void onEnergyChanged(int energy);    // Updates the protagonist's visual representation
    void onDirectionChanged(Player::Direction dir);
    void checkHealthPackCollision();
    void setPoisonEffect();

};

#endif // PROTAGONISTVIEW2D_H
