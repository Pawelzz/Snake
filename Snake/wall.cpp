#include "wall.h"

//Wall::Wall()
//{

//}

Wall::Wall(const float &pos_x, const float &pos_y)
{
    texture_wall.loadFromFile("Textures/wall.png");
    texture_wall.setSmooth(true);
    setTexture(texture_wall);
    setScale(0.5,0.5);
    setPosition(pos_x, pos_y);
}

Wall::Wall()
{
    texture_wall.loadFromFile("Textures/sandstone.jpg");
    texture_wall.setSmooth(true);
    texture_wall.setRepeated(true);
    setTexture(texture_wall);
    setPosition(0,700);
    setTextureRect(sf::IntRect(0, 0, 1200, 50));
}
