#ifndef PROTAGONISTVIEWTEXT_H
#define PROTAGONISTVIEWTEXT_H

#include "Model/player.h"
#include "View/gameobjecttextview.h"
#include "qgraphicsitem.h"
#include <QFont>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPen>
#include <QPropertyAnimation>
#include <QTimer>

class ProtagonistViewText : public GameObjectTextView {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos) // Ensure Q_PROPERTY for pos is declared

  public:
    ProtagonistViewText(const std::unique_ptr<Player> &protagonist, double tileWidth, double tileHeight, QFont font);

  protected:
    int getNrOfFramesIdle() const override { return 16; }
    int getNrOfFramesWalking() const override { return 16; }
    int getNrOfFramesFighting() const override { return 16; }
    int getNrOfFramesDying() const override { return 0; }

  private:
    QPropertyAnimation *movementAnimation; // Animation for position movement
    QTimer *poisonTimer;                   // Timer for the poison effect
    Player::Direction currentDirection;

  private slots:
    void onPositionChanged(int x, int y); // Updates the protagonist's position
    void onHealthChanged(int health);     // Updates the protagonist's visual representation
    void onEnergyChanged(int energy);     // Updates the protagonist's visual representation
    void checkHealthPackCollision();
    void onPlayerAttack();
    void setPoisonEffect();
    void onDirectionChanged(Player::Direction dir);
    void setAnimation() override;
};

#endif // PROTAGONISTVIEWTEXT_H
