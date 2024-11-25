#ifndef PROTAGONISTVIEW2D_H
#define PROTAGONISTVIEW2D_H

#include <QObject>
#include <QGraphicsPixmapItem>

#include "world.h"

class ProtagonistView2D : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    ProtagonistView2D(const std::unique_ptr<Protagonist>& protagonist, std::size_t gridSize, QGraphicsItem* parent = nullptr);

private:
    std::size_t gridSize{};

private slots:
    void onPositionChanged(int x, int y); // Updates the protagonist's position
    //void onHealthChanged(int health);    // Updates the protagonist's visual representation
    void onEnergyChanged(int energy);    // Updates the protagonist's visual representation
};

#endif // PROTAGONISTVIEW2D_H
