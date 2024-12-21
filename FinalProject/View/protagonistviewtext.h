#ifndef PROTAGONISTVIEWTEXT_H
#define PROTAGONISTVIEWTEXT_H

#include "Model/player.h"
#include "qgraphicsitem.h"
#include "world.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPropertyAnimation>
#include <QFont>
#include <QTimer>
#include <QPen>

class ProtagonistViewText : public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos) // Ensure Q_PROPERTY for pos is declared

  public:
    ProtagonistViewText(const std::unique_ptr<Player> &protagonist, double tileWidth, double tileHeight, QFont font,  QGraphicsItem *parent = nullptr);

  private:
    double tileWidth, tileHeight;
    QFont font;
    enum AnimationState { Idle,
                          Walking,
                          Fighting,
                          Dying }; // Animation states
    AnimationState currentState;   // Current animation state

    QPropertyAnimation *movementAnimation; // Animation for position movement
    QTimer *animationTimer;                // Timer for cycling pixmaps
    int currentFrameIndex;                 // Current frame index in pixmap arrays

    void setState(AnimationState newState); // Switch animation state
    QPen pen;

  private slots:
    void onPositionChanged(int x, int y); // Updates the protagonist's position
    void onHealthChanged(int health);     // Updates the protagonist's visual representation
    void onEnergyChanged(int energy);     // Updates the protagonist's visual representation
    void updateAnimationFrame();          // Update animation frame
};

#endif // PROTAGONISTVIEWTEXT_H
