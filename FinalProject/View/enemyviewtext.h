#ifndef ENEMYVIEWTEXT_H
#define ENEMYVIEWTEXT_H

#include "qfont.h"
#include "qgraphicsitem.h"
#include "qobject.h"
#include "world.h"
class EnemyViewText : public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT

  public:
    EnemyViewText(const std::unique_ptr<Enemy> &enemy, double tileWidth, double tileHeight, QFont font, QGraphicsItem *parent = nullptr);

  private:
    double tileWidth, tileHeight;
    QFont font;
    QTimer *animationTimer;

  private slots:
    void updateAnimationFrame();
};

#endif // ENEMYVIEWTEXT_H
