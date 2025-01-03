#ifndef XENEMYVIEWTEXT_H
#define XENEMYVIEWTEXT_H

#include "Model/enemywrapper.h"
#include "qfont.h"
#include "qgraphicsitem.h"
#include "qobject.h"
#include "qpen.h"
#include "world.h"

class XEnemyViewText : public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT

  public:
    XEnemyViewText(const std::unique_ptr<EnemyWrapper> &enemy, double tileWidth, double tileHeight, QFont font, QGraphicsItem *parent = nullptr);

  private:
    double tileWidth, tileHeight;
    QFont font;
    QTimer *animationTimer;
    QPen pen;
    int currentFrameIndex;
    bool transformed;

  private slots:
    void updateAnimationFrame();
    void onDefeated();
    void onTransform();
};

#endif // XENEMYVIEWTEXT_H
