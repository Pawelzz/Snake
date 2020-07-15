#ifndef BOOST_H
#define BOOST_H
#include "elementsceny.h"

class Boost : public ElementSceny
{
private:
    Texture txt;
public:
    Boost()
    {
        txt.loadFromFile("star.png");
        txt.setSmooth(true);
        setTexture(txt);
        setScale(0,0);
    }

//    void resp(Clock &czas, sf::RenderWindow &window)
//    {
//        if(czas.getElapsedTime().asSeconds()>10)
//        {
//            setPosition((rand()%1137), (rand()%687));
//            setScale(0.1,0.1);
//            window.draw()
//        }
//    }
};

#endif // BOOST_H
