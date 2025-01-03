#ifndef PENEMYVIEWTEXT_H
#define PENEMYVIEWTEXT_H

#include "Model/enemywrapper.h"
#include "qfont.h"
#include "qgraphicsitem.h"
#include "qobject.h"
#include "qpen.h"
#include "world.h"
class PEnemyViewText : public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT

  public:
    PEnemyViewText(const std::unique_ptr<EnemyWrapper> &enemy, double tileWidth, double tileHeight, QFont font, QGraphicsItem *parent = nullptr);
    void setPoisonCircle(int value);

  private:
    double tileWidth, tileHeight;
    QFont font;
    QTimer *animationTimer;
    QPen pen;
    int currentFrameIndex;
    QGraphicsTextItem* poisonCircle;
    void expandPoisonCircle(int value);
    bool died;

  private slots:
    void onDefeated();
    void onPoisonLevelValueUpdated(int value);
    void updateAnimationFrame();
};

#endif // PENEMYVIEWTEXT_H
