#ifndef WORLDVIEWTEXT_H
#define WORLDVIEWTEXT_H

#include "View/worldview.h"
#include "qfont.h"
#include <QGraphicsTextItem>
#include <QGraphicsSimpleTextItem>

#include <QObject>
#include <QGraphicsScene>

class WorldViewText:  public WorldView, public QObject
{
  public:
    WorldViewText();
    QGraphicsScene *makeScene() const override;
    void updateGrid(int xPos, int yPos);
    void setSize(int size);

  private:
    int size{50};
    QColor darkGreen{0, 75, 0};  // Dark green color
    QColor lightGreen{144, 238, 144};  // Light green color
    QFont font{"Monospace"};
    QGraphicsTextItem *bgText1;
    /*QGraphicsTextItem *bgText2;*/
    /*QGraphicsTextItem *bgText3;*/
    /*QGraphicsTextItem *bgText4;*/
    QGraphicsSimpleTextItem *borders;

    QString pixmapToString(const QPixmap &pixmap, int xPos, int yPos) const;
};

#endif // WORLDVIEWTEXT_H
