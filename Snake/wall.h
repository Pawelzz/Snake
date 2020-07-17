#ifndef WALL_H
#define WALL_H
#include "elementsceny.h"


class Wall :public ElementSceny
{
private:
    Texture texture_wall;
public:
    Wall(float const &pos_x, float const &pos_y);
    Wall();
};

#endif // WALL_H
