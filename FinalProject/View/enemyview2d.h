#ifndef ENEMYVIEW2D_H
#define ENEMYVIEW2D_H

#include <QGraphicsPixmapItem>
#include <world.h>

class EnemyView2D : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    EnemyView2D(const std::unique_ptr<Enemy>& enemy, std::size_t gridSize, QGraphicsItem* parent = nullptr);
    EnemyView2D(const std::unique_ptr<Enemy>& enemy, std::size_t gridSize, QString filename, QGraphicsItem* parent = nullptr);
    virtual ~EnemyView2D() = default;

protected:
    virtual void updatePixMap();

protected:
    std::size_t gridSize{};

private slots:
    void onDeadUpdated();
};

#endif // ENEMYVIEW2D_H
