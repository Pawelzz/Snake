#ifndef WALL_H
#define WALL_H
#include "elementsceny.h"


class Wall :public ElementSceny
{
private:

    Texture texture_wall;
public:
    Wall(float const &pos_x, float const &pos_y)
    {
        texture_wall.loadFromFile("wall.png");
        texture_wall.setSmooth(true);
        setTexture(texture_wall);
        setScale(0.5,0.5);
        setPosition(pos_x, pos_y);
    }
    Wall()
    {
        texture_wall.loadFromFile("sandstone.jpg");
        texture_wall.setSmooth(true);
        texture_wall.setRepeated(true);
        setTexture(texture_wall);
        setPosition(0,700);
        setTextureRect(sf::IntRect(0, 0, 1200, 50));
    }
};

#endif // WALL_H
