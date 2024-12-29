#ifndef ENEMYVIEWTEXT_H
#define ENEMYVIEWTEXT_H

#include "qfont.h"
#include "qgraphicsitem.h"
#include "qobject.h"
#include "qpen.h"
#include "world.h"
class EnemyViewText : public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT

  public:
    EnemyViewText(const std::unique_ptr<Enemy> &enemy, double tileWidth, double tileHeight, QFont font, QGraphicsItem *parent = nullptr);

  private:
    double tileWidth, tileHeight;
    QFont font;
    QPen pen;
    QTimer *animationTimer;
    int currentFrameIndex;

  private slots:
    void updateAnimationFrame();
};

#endif // ENEMYVIEWTEXT_H
