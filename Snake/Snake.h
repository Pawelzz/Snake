#ifndef SNAKE_H
#define SNAKE_H
#include "elementsceny.h"

#endif // SNAKE_H

class SnakeElement :public ElementSceny
{
    public:Texture texture;
    public:Vector2f position;
    public:SnakeElement(Texture txt, float x, float y)
    {
        texture = txt;
        position.x = x;
        position.y = y;
        texture.loadFromFile("snake-graphics.png");
        setPosition(position.x,position.y);
        texture.setSmooth(true);
        setTexture(texture);
        setTextureRect(sf::IntRect(256, 0, 64, 64));
    }
    public:void UpdatePart()
    {
        setPosition(position.x,position.y);
//        texture.loadFromFile("snake-graphics.png");
    }
};

using SnakeBody = vector<SnakeElement>;
enum class Direction {None, Up, Down, Left, Right};

class Snake :public ElementSceny
{
private:
    Texture texture;
    bool w_gore=0;
    bool w_dol=0;
    bool w_prawo=0;
    bool w_lewo=0;

    float vel_x=0;
    float vel_y=0;

public:


    float pos_x;
    float pos_y;

    SnakeBody m_snake;


    //    float zycie;
    int ilosc_segmentow=1;
    //    bool przenikalnosc;


public:
    Snake()
    {
        texture.loadFromFile("snake-graphics.png");
        //texture.setSmooth(true);
        setTexture(texture);
        setTextureRect(sf::IntRect(256, 0, 64, 64));
        setPosition(500.0, 400.0);
        m_snake.push_back(SnakeElement(texture,getPosition().x,getPosition().y));
    }
    Direction m_dir;

    void rozszerzenie()
    {
        SnakeElement &Last = m_snake[m_snake.size()-1];
        if(m_snake.size()>1)
        {
            SnakeElement &Second = m_snake[m_snake.size()-2];

            if(Last.position.x == Second.position.x)
            {
                if(Last.position.y > Second.position.y)
                {
                    m_snake.push_back(SnakeElement(Last.texture,Last.position.x, Last.position.y+64));
                }
                else
                {
                    m_snake.push_back(SnakeElement(Last.texture,Last.position.x, Last.position.y-64));
                }
            }
            else if(Last.position.y == Second.position.y)
            {
                if(Last.position.x>Second.position.x)
                {
                    m_snake.push_back(SnakeElement(Last.texture,Last.position.x+64, Last.position.y));
                }
                else
                {
                    m_snake.push_back(SnakeElement(Last.texture,Last.position.x-64, Last.position.y));
                }
            }
        }
        else
        {
            switch(m_dir)
            {
                case Direction::Up:
                    m_snake.push_back(SnakeElement(Last.texture,Last.position.x, Last.position.y+64));
                    break;
                case Direction::Down:
                    m_snake.push_back(SnakeElement(Last.texture,Last.position.x, Last.position.y-64));
                    break;
                case Direction::Left:
                    m_snake.push_back(SnakeElement(Last.texture,Last.position.x+64, Last.position.y));
                    break;
                case Direction::Right:
                    m_snake.push_back(SnakeElement(Last.texture,Last.position.x-64, Last.position.y));
                    break;
                case Direction::None:
                    break;
            }
        }
//        m_snake[m_snake.size()-1].texture.loadFromFile("snake-graphics.png");
//        setTexture(m_snake[m_snake.size()-1].texture);

    }

    void bodyanimate(Clock &Czas)
    {
        //cout<<Czas.getElapsedTime().asSeconds()<<endl;
        if(Czas.getElapsedTime().asSeconds()>0.08)
        {
            for(int i=m_snake.size()-1;i>0;--i)
            {
                m_snake[i].position = m_snake[i-1].position;
                m_snake[i].UpdatePart();
                Czas.restart();
            }
        }
    }

    void animate()
    {
        m_snake[0].position.x = getPosition().x;
        m_snake[0].position.y = getPosition().y;
        m_snake[0].UpdatePart();

        if(w_prawo)
        {
            vel_x=0.5;
            vel_y=0;
            move(vel_x,vel_y);
            setTextureRect(sf::IntRect(256, 0, 64, 64));
            m_dir = Direction::Right;
        }
        if(w_lewo)
        {
            vel_x=-0.5;
            vel_y=0;
            move(vel_x,vel_y);
            setTextureRect(sf::IntRect(192, 64, 64, 64));
            m_dir = Direction::Left;
        }
        if(w_gore)
        {
            vel_x=0;
            vel_y=-0.5;
            move(vel_x,vel_y);
            setTextureRect(sf::IntRect(192, 0, 64, 64));
            m_dir = Direction::Up;
        }
        if(w_dol)
        {
            vel_x=0;
            vel_y=0.5;
            move(vel_x,vel_y);
            setTextureRect(sf::IntRect(256, 64, 64, 64));
            m_dir = Direction::Down;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && w_lewo==0)
        {
            w_prawo=1;
            w_dol=0;
            w_gore=0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && w_prawo==0)
        {
            w_lewo=1;
            w_gore=0;
            w_dol=0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && w_dol==0)
        {
            w_gore=1;
            w_lewo=0;
            w_prawo=0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && w_gore==0)
        {
            w_dol=1;
            w_lewo=0;
            w_prawo=0;
        }

        if (getGlobalBounds().left<0)
        {
            setPosition(600,350);
        }
        if (getGlobalBounds().left+getGlobalBounds().width>1200)
        {
            setPosition(600,350);
        }
        if (getGlobalBounds().top<0)
        {
            setPosition(600,350);
        }
        if (getGlobalBounds().top+getGlobalBounds().height>750)
        {
            setPosition(600,350);
        }
    }

    void jedzenie(ElementSceny &element)
    {
        if(getGlobalBounds().intersects(element.getGlobalBounds()))
        {
            element.setPosition((rand()%1137), (rand()%687));
            ilosc_segmentow+=1;
            rozszerzenie();
            cout << "segmenty: "<<ilosc_segmentow<<endl;
        }
    }

};
