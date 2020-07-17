#ifndef BOOST_H
#define BOOST_H
#include "elementsceny.h"
#include "Snake.h"
#include "wall.h"

//class Boost : public ElementSceny
//{
//private:
//    Texture txt;
//    float counter;
//public:
//    Boost()
//    {
//        txt.loadFromFile("star.png");
//        txt.setSmooth(true);
//        setTexture(txt);
//        setScale(0.1,0.1);

//        if(rand()%4== 0)
//        {
//            setPosition(50,50);
//        }
//        if(rand()%4== 1)
//        {
//            setPosition(1115,40);
//        }
//        if(rand()%4== 2)
//        {
//            setPosition(40,615);
//        }
//        if(rand()%4== 3)
//        {
//            setPosition(1115,615);
//        }
//    }

//    Boost(float const &x)
//    {
//        txt.loadFromFile("empty_star.png");
//        txt.setSmooth(true);
//        setTexture(txt);
//        setScale(0.1,0.1);
//        setPosition(x*655,x*710);
//    }

//    float get_couter()
//    {
//        return counter;
//    }

//    void zebranie(Snake &snake, Clock &czas)
//    {
//        if(snake.get_snake_head().getGlobalBounds().intersects(getGlobalBounds()) && snake.get_przenikalnosc()==false)
//        {
//            snake.set_przenikalnosc(true);
//            setPosition(655,710);
//            czas.restart();
//        }
//        if(snake.get_przenikalnosc()==true)
//        {
//            counter=czas.getElapsedTime().asSeconds();
//            if(counter>=10)
//            {
//                snake.set_przenikalnosc(false);
//            }
//        }
//    }
//};

#endif // BOOST_H
