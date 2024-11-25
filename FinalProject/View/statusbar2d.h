#ifndef STATUSBAR2D_H
#define STATUSBAR2D_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

class StatusBar2D : public QObject, public QGraphicsRectItem
{
Q_OBJECT

public:
    StatusBar2D(const std::size_t x, const std::size_t y, const Qt::GlobalColor color, QGraphicsItem* parent = nullptr);

private:
    int maxValue {100};
    int currentValue {100};

public slots:
    void updateBar(int newValue);
};

#endif // STATUSBAR2D_H
