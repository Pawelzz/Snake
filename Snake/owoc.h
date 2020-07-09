#ifndef OWOC_H
#define OWOC_H
#include "elementsceny.h"


class Owoc :public ElementSceny
{
private:
    Texture texture;
public:
    Owoc()
    {
        texture.loadFromFile("snake-graphics.png");
        texture.setSmooth(true);
        setTexture(texture);
        setTextureRect(sf::IntRect(0, 192, 64, 64));
        setPosition(100.0, 100.0);
    }
};

#endif // OWOC_H
