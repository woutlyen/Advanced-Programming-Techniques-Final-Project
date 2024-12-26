#include "penemyview2d.h"
#include "qbrush.h"
#include <QPen>

PEnemyView2D::PEnemyView2D(const std::unique_ptr<EnemyWrapper> &enemy, std::size_t gridSize) :EnemyView2D(enemy, gridSize, true) {

    initializeEnemy2DView();
    // Connect signals & slots
    connect(enemy.get(), &EnemyWrapper::dead, this, &PEnemyView2D::onDefeated);
    connect(static_cast<PEnemyWrapper*>(enemy.get()), &PEnemyWrapper::startPoison, this, &PEnemyView2D::setPoisonCircle);
    connect(static_cast<PEnemyWrapper*>(enemy.get()), &PEnemyWrapper::poisonLevelUpdated, this, &PEnemyView2D::onPoisonLevelValueUpdated);
}


void PEnemyView2D::setPoisonCircle(int value)
{
    poisonCircle = LevelController::getInstance().generatePoisonedCircle(x(), y(), value);
    QTimer::singleShot(2000, this, &PEnemyView2D::expandPoisonCircle);
    setState(AnimationState::Fighting);
}

void PEnemyView2D::expandPoisonCircle()
{
    QRectF currentRect = poisonCircle->rect();

    // Calculate the new position and size based on the new radius
    qreal newX = currentRect.center().x() - gridSize*5 / 2;
    qreal newY = currentRect.center().y() - gridSize*5 / 2;
    qreal newWidth = gridSize*5;
    qreal newHeight = gridSize*5;

    // Set the new rectangle with the updated radius
    poisonCircle->setRect(newX, newY, newWidth, newHeight);
}

void PEnemyView2D::onDefeated()
{
    if(currentState != Dying){
        setState(Dying);
        poisonCircle->setBrush(QColor(83, 0, 128, 0));
        QTimer::singleShot(2000, this, [this]() {LevelController::getInstance().removePoisonedCircle(poisonCircle);});
    }
}

void PEnemyView2D::onPoisonLevelValueUpdated(int value)
{
    poisonCircle->setBrush(QColor(83, 0, 128, (value*255)/(100)));
}
