#ifndef NODE_H
#define NODE_H

#include "world.h"

class Node : public Tile
{
public:
    Node(int x, int y, float value);
    float f{0};
    float g{0};
    float h{0};
    bool visited{false};
    bool closed{false};
    Node* prev;
};

#endif // NODE_H
