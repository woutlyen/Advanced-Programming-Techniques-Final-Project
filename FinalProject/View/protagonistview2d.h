#ifndef PROTAGONISTVIEW2D_H
#define PROTAGONISTVIEW2D_H

#include <QObject>
#include <QGraphicsPixmapItem>

#include "world.h"
#include "statusbar.h"

class ProtagonistView2D : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    ProtagonistView2D(const std::unique_ptr<Protagonist>& protagonist, std::size_t gridSize, QGraphicsItem* parent = nullptr);

private:
    std::size_t gridSize{};
    StatusBar* healthBar;
    StatusBar* energyBar;

private slots:
    void onPositionChanged(int x, int y); // Updates the protagonist's position
    //void onHealthChanged(int health);    // Updates the protagonist's health bar or visual representation
    //void onEnergyChanged(int energy);    // Updates the protagonist's energy bar or visual representation
};

#endif // PROTAGONISTVIEW2D_H
