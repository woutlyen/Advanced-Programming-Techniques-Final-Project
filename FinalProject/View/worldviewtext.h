#ifndef WORLDVIEWTEXT_H
#define WORLDVIEWTEXT_H

#include "View/worldview.h"

#include <QObject>
#include <QGraphicsScene>

class WorldViewText:  public WorldView
{
  public:
    QGraphicsScene *makeScene() const override;

  private:
    QColor darkGreen{0, 75, 0};  // Dark green color
    QColor lightGreen{144, 238, 144};  // Light green color
    QString pixmapToString(const QPixmap &pixmap) const;
};

#endif // WORLDVIEWTEXT_H
