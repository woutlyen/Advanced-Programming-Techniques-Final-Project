#ifndef NODE_H
#define NODE_H

#include "world.h"

class Node : public Tile
{
public:
    Node(int x, int y, float value);
    float f;
    float g;
    float h;
    bool visited{false};
    bool closed{false};
    Node* prev;
};

#endif // NODE_H
