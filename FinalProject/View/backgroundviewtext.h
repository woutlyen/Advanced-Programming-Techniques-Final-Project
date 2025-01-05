#ifndef BACKGROUNDVIEWTEXT_H
#define BACKGROUNDVIEWTEXT_H

#include "qobject.h"
#include "qpixmap.h"
#include "qtmetamacros.h"
class BackgroundViewText : public QObject {
    Q_OBJECT

  public slots:
    void pixmapToString(const QPixmap &pixmap, int xPos, int yPos, int size);
    void fastPixmapToString(const QPixmap &pixmap, int xPos, int yPos, int size);
  signals:
    void stringReady(const QString &result, int xPos, int yPos);
};

#endif
