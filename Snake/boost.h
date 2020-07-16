#ifndef BOOST_H
#define BOOST_H
#include "elementsceny.h"
#include "Snake.h"

class Boost : public ElementSceny
{
private:
    Texture txt;
    float counter;
public:
    Boost()
    {
        txt.loadFromFile("star.png");
        txt.setSmooth(true);
        setTexture(txt);
        setScale(0.1,0.1);
        setPosition((rand()%1137), (rand()%687));
    }

    float get_couter()
    {
        return counter;
    }

    void zebranie(Snake &snake, Clock &czas)
    {
        if(getGlobalBounds().intersects(snake.m_snake[0].getGlobalBounds()) && snake.get_przenikalnosc()==false)
        {
            snake.set_przenikalnosc(true);
            setPosition(655,710);
            czas.restart();
        }
        if(snake.get_przenikalnosc()==true)
        {
            counter=czas.getElapsedTime().asSeconds();
            if(counter>=10)
            {
                snake.set_przenikalnosc(false);


            }
        }
    }
};

#endif // BOOST_H
