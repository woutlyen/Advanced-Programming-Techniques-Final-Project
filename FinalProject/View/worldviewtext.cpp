#include "worldviewtext.h"

WorldViewText::WorldViewText() {}

QGraphicsScene *WorldViewText::makeScene(std::vector<std::unique_ptr<Enemy> > &enemies, std::vector<std::unique_ptr<Tile> > &healthPacks, std::unique_ptr<Protagonist> &protagonist, int rows, int columns, QString filename, std::size_t gridSize)
{
    QGraphicsScene* scene = new QGraphicsScene();

    return scene;
}
