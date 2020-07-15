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
        setScale(0.5,0.5);
    }
//    Owoc(int const &z)
//    {
//        texture.loadFromFile("score.png");
//        texture.setSmooth(true);
//        setTexture(texture);
////        setTextureRect(sf::IntRect(0,0, 64, 64));
//        setPosition(z*1000, z*710);
//        setScale(0.5,0.5);
//    }

    void owoc_resp(ElementSceny &el)
    {
        if(getGlobalBounds().intersects(el.getGlobalBounds()))
        {
            setPosition((rand()%1137), (rand()%687));
        }
    }


};

#endif // OWOC_H
