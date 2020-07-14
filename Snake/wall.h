#ifndef WALL_H
#define WALL_H
#include "elementsceny.h"


class Wall :public ElementSceny
{

    Texture texture_wall;
public:
    Wall(float pos_x, float pos_y)
    {
        texture_wall.loadFromFile("wall.png");
        texture_wall.setSmooth(true);
        setTexture(texture_wall);
        setScale(0.5,0.5);
        setPosition(pos_x, pos_y);
    }
};

#endif // WALL_H
