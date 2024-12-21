#ifndef HEALTHPACKVIEW2D_H
#define HEALTHPACKVIEW2D_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "world.h"

class HealthPackView2D : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    HealthPackView2D(const std::unique_ptr<Tile>& healthPack, std::size_t gridSize, QGraphicsItem* parent = nullptr);
    void playPickupAnimation();

private:
    std::size_t gridSize{};
    QTimer* animationTimer;                // Timer for cycling pixmaps
    std::vector<QPixmap> heartPixmaps;     // Pixmaps for the animation
    int currentFrameIndex;                 // Current frame index in pixmap array
    qreal currentOpacity {1.0};

    std::vector<QPixmap> extractFrames(const QString& filePath, int frameWidth, int frameHeight, int numberOfFrames);

private slots:
    void updateAnimationFrame(); // Update animation frame
};

#endif // HEALTHPACKVIEW2D_H
