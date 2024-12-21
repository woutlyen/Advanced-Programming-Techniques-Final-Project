#include "healthpackview2d.h"

#include <QPropertyAnimation>
#include <QTimer>

HealthPackView2D::HealthPackView2D(const std::unique_ptr<Tile>& healthPack, std::size_t gridSize, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent), animationTimer(new QTimer(this)), currentFrameIndex{0}
{

    this->gridSize = gridSize;
    heartPixmaps = extractFrames(":/images/hearts.png", 32, 32, 8);

    // Set the initial pixmap
    setPixmap(heartPixmaps[0]);
    setPos(gridSize*healthPack->getXPos(), gridSize*healthPack->getYPos());

    // Configure the animation timer
    animationTimer->setInterval(100); // Frame switch interval (in milliseconds)
    animationTimer->start();
    connect(animationTimer, &QTimer::timeout, this, &HealthPackView2D::updateAnimationFrame);
}

void HealthPackView2D::updateAnimationFrame() {
        // Cycle through idle frames
        currentFrameIndex = (currentFrameIndex + 1) % heartPixmaps.size();
        setPixmap(heartPixmaps[currentFrameIndex]);
}

std::vector<QPixmap> HealthPackView2D::extractFrames(const QString& filePath, int frameWidth, int frameHeight, int numberOfFrames) {
    std::vector<QPixmap> frames;

    // Load the full spritesheet
    QPixmap spriteSheet(filePath);

    // Extract each frame
    for (int i = 0; i < numberOfFrames; ++i) {
        QPixmap frame = spriteSheet.copy(i * spriteSheet.width()/numberOfFrames + ((spriteSheet.width()/numberOfFrames)-frameWidth)/2, (spriteSheet.height()-frameHeight)/2, frameWidth, frameHeight);
        frames.push_back(frame.scaledToHeight(gridSize));
    }

    return frames;
}

void HealthPackView2D::playPickupAnimation()
{
    // Stop idle animation
    //animationTimer->stop();

    // Start fade-out animation
    QTimer* fadeTimer = new QTimer(this); // Timer to control opacity reduction
    connect(fadeTimer, &QTimer::timeout, this, [this, fadeTimer]() {
        currentOpacity -= 0.05; // Decrease opacity gradually
        if (currentOpacity <= 0.0) {
            currentOpacity = 0.0;
            fadeTimer->stop(); // Stop the timer once fully transparent
            fadeTimer->deleteLater();

            // Remove item from the scene and delete it
            if (scene()) {
                //scene()->removeItem(this);
            }
            delete this;
        } else {
            // Apply the new opacity
            setOpacity(currentOpacity);
        }
    });

    fadeTimer->start(30); // Trigger every 50ms for smooth fade-out
}
