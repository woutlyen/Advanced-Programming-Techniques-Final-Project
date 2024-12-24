#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include <QGraphicsScene>

class WorldView
{
public:
    virtual ~WorldView(){};
    virtual QGraphicsScene* makeScene() const = 0;
};

#endif // WORLDVIEW_H
