#include "owoc.h"

Owoc::Owoc()
{
    texture.loadFromFile("Textures/snake-graphics.png");
    texture.setSmooth(true);
    setTexture(texture);
    setTextureRect(sf::IntRect(0, 192, 64, 64));
    setPosition(100.0, 100.0);
    setScale(0.5,0.5);
}

void Owoc::owoc_spawn()
{
    setPosition((rand()%1137), (rand()%687));
}

void Owoc::owoc_resp(const Wall &el)
{
    if(getGlobalBounds().intersects(el.getGlobalBounds()))
    {
        setPosition((rand()%1137), (rand()%687));
    }
}
