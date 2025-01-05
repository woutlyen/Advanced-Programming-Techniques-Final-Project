#ifndef WORLDVIEWTEXT_H
#define WORLDVIEWTEXT_H

#include "View/backgroundviewtext.h"
#include "View/worldview.h"
#include "qfont.h"
#include "qthread.h"
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
    void setSize(int size);
    QGraphicsTextItem *addPoisonCircle(int x, int y, int radius, QGraphicsScene *scene, int value);
    void removePoisonCircle(QGraphicsTextItem *poisonCircle, QGraphicsScene *scene);

  private:
    int size{35};
    QColor darkGreen{0, 75, 0};       // Dark green color
    QColor lightGreen{144, 238, 144}; // Light green color
    QFont font{"Monospace"};
    QGraphicsTextItem *bgText1;
    QGraphicsSimpleTextItem *borders;
    BackgroundViewText *bgWorker;
    QThread bgThread;

    QString pixmapToString(const QPixmap &pixmap, int xPos, int yPos) const;

  public slots:
    void setGrid(const QString &bg, int xPos, int yPos);
    void updateGrid(int xPos, int yPos);
  signals:
    void createBg(const QPixmap &pixmap, int xPos, int yPos, int size);
    void createFastBg(const QPixmap &pixmap, int xPos, int yPos, int size);
};

#endif // WORLDVIEWTEXT_H
