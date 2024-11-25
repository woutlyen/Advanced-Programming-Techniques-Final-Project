#include "statusbar.h"

StatusBar::StatusBar(const std::size_t x, const std::size_t y, const Qt::GlobalColor color, QGraphicsItem *parent)
    : QGraphicsRectItem(parent){
    // Set the default dimensions of the bar
    setRect(0, 0, 200, 15);
    setBrush(QBrush(color));
    setPen(QPen(Qt::NoPen)); // No border
    setPos(x,y);
    setOpacity(0.75);
}

void StatusBar::updateBar(int newValue)
{
    currentValue = newValue;

    // Adjust the width of the bar based on the current value
    QRectF newRect(0, 0, 2*newValue, rect().height());
    QGraphicsRectItem::setRect(newRect);

    // Change color based on value (green -> yellow -> red)
    if (currentValue > maxValue * 0.5) {
        setBrush(QBrush(Qt::green));
    } else if (currentValue > maxValue * 0.25) {
        setBrush(QBrush(Qt::yellow));
    } else {
        setBrush(QBrush(Qt::red));
    }
}
