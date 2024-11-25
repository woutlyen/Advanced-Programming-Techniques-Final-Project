#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

class StatusBar : public QObject, public QGraphicsRectItem
{
Q_OBJECT

public:
    StatusBar(const std::size_t x, const std::size_t y, const Qt::GlobalColor color, QGraphicsItem* parent = nullptr);

private:
    int maxValue {100};
    int currentValue {100};

public slots:
    void updateBar(int newValue);
};

#endif // STATUSBAR_H
