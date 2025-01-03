#ifndef WORLDVIEWTEXT_H
#define WORLDVIEWTEXT_H

#include "View/worldview.h"
#include "qfont.h"
#include "qtmetamacros.h"
#include <QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>

#include <QGraphicsScene>
#include <QObject>

class WorldViewText : public QObject, public WorldView {
    Q_OBJECT
  public:
    WorldViewText();
    QGraphicsScene *makeScene() const override;
    void updateGrid(int xPos, int yPos);
    void setSize(int size);
    QGraphicsTextItem *addPoisonCircle(int x, int y, int radius, QGraphicsScene *scene, int value);
    void removePoisonCircle(QGraphicsTextItem *poisonCircle, QGraphicsScene *scene);

  private:
    int size{50};
    QColor darkGreen{0, 75, 0};       // Dark green color
    QColor lightGreen{144, 238, 144}; // Light green color
    QFont font{"Monospace"};
    QGraphicsTextItem *bgText1;
    QGraphicsSimpleTextItem *borders;

    QString pixmapToString(const QPixmap &pixmap, int xPos, int yPos) const;
};

#endif // WORLDVIEWTEXT_H
