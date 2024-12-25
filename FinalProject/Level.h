#ifndef LEVEL_H
#define LEVEL_H

#include "Model/enemywrapper.h"
#include "Model/player.h"

#include <vector>
#include <memory>
#include <QString>
#include <world.h>
#include <QGraphicsScene>

struct Level {
    int number;
    int xpos;
    int ypos;
    int healthpacks;
    int enemyNr;
    float pratio;
    float xratio;
    QString visual_map;
    QString data_map;
    int grid_size;
    int visual_grid_size;
    int prev_level_x_pos;
    int prev_level_y_pos;
    int next_level_x_pos;
    int next_level_y_pos;

    std::vector<std::unique_ptr<Tile>> tiles;
    std::vector<std::unique_ptr<EnemyWrapper>> enemies;
    std::vector<std::unique_ptr<Tile>> healthPacks;
    std::unique_ptr<Player> protagonist;

    int width;
    int height;

    QGraphicsScene * scenesText;
    QGraphicsScene * scenes2D;
};

#endif // LEVEL_H
