#ifndef SNAKE_H
#define SNAKE_H
#include "elementsceny.h"
#include "owoc.h"
#include "wall.h"

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
        texture.loadFromFile("body.png");
        setPosition(position.x,position.y);
        texture.setSmooth(true);
        setTexture(texture);
        setScale(0.7,0.7);
    }
public:void UpdatePart()
    {
        setPosition(position.x,position.y);
        setTexture(texture);
    }
};

using SnakeBody = vector<SnakeElement>;
enum class Direction {None, Up, Down, Left, Right};

class Snake :public ElementSceny
{
private:
    Texture texture_head;
    Texture texture_body;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    sf::SoundBuffer buffer2;
    sf::Sound sound2;

    bool b_kolizja_sciana=false;

    int ilosc_segmentow=0;

    bool przenikalnosc;

    float tempo;

    bool w_gore=0;
    bool w_dol=0;
    bool w_prawo=0;
    bool w_lewo=0;


public:

    SnakeBody m_snake;




public:
    Snake()
    {
        texture_head.loadFromFile("snake-graphics.png");
        //texture.setSmooth(true);
        setTexture(texture_head);
        setTextureRect(sf::IntRect(256, 0, 64, 64));
        setScale(0.7,0.7);
        setPosition(500.0, 400.0);
        m_snake.push_back(SnakeElement(texture_head,getPosition().x,getPosition().y));
        buffer.loadFromFile("bite.wav");
        buffer2.loadFromFile("self-bite.wav");
        sound.setBuffer(buffer);
        sound2.setBuffer(buffer2);
        przenikalnosc=0;
        tempo=0.002;
        for(int i = 0;i<2;i++)
        {
            rozszerzenie();
        }
    }
    Direction m_dir;

    void rozszerzenie()
    {
        SnakeElement &Last = m_snake[m_snake.size()-1];
        if(m_snake.size()>1)
        {
            //SnakeElement &Second = m_snake[m_snake.size()-2];

            /*if(Last.position.x == Second.position.x)
            {
                if(Last.position.y > Second.position.y)
                {
                    m_snake.push_back(SnakeElement(Last.texture,Last.position.x, Last.position.y+100));
                }
                else
                {
                    m_snake.push_back(SnakeElement(Last.texture,Last.position.x, Last.position.y-100));
                }
            }
            else if(Last.position.y == Second.position.y)
            {
                if(Last.position.x>Second.position.x)
                {
                    m_snake.push_back(SnakeElement(Last.texture,Last.position.x+100, Last.position.y));
                }
                else
                {
                    m_snake.push_back(SnakeElement(Last.texture,Last.position.x-100, Last.position.y));
                }
            }*/
            m_snake.push_back(SnakeElement(Last.texture,Last.position.x, Last.position.y));
        }
        else
        {
            m_snake.push_back(SnakeElement(Last.texture,Last.position.x, Last.position.y));
            m_snake[0].texture.loadFromFile("transparent.png");
            m_snake[0].setTexture(m_snake[0].texture);
            rozszerzenie();
        }

    }

    int get_score()
    {
        return get_ilosc_segmentow()-4;
    }

    int get_ilosc_segmentow()
    {
        ilosc_segmentow=m_snake.size();
        return ilosc_segmentow;
    }

    bool get_b_kolizja_sciana()
    {
        return b_kolizja_sciana;
    }

    SnakeBody get_snake_body()
    {
        return m_snake;
    }

    void bodyanimate(Clock &Czas2)
    {
        if(Czas2.getElapsedTime().asSeconds()>0.09)
        {
            for(int i=m_snake.size()-1;i>=0;i--)
            {
                m_snake[i].position = m_snake[i-1].position;
                m_snake[i].UpdatePart();
                Czas2.restart();
            }
        }
    }

    void animate(Clock &Czas)
    {
        b_kolizja_sciana=false;
        m_snake[0].position.x = getPosition().x;
        m_snake[0].position.y = getPosition().y;
        m_snake[0].UpdatePart();
        if(Czas.getElapsedTime().asSeconds()>tempo)
        {


            if(w_prawo)
            {
                setPosition(getPosition().x+1,getPosition().y);
                setTextureRect(sf::IntRect(255, 1, 62, 62));
                m_dir = Direction::Right;
            }
            if(w_lewo)
            {
                setPosition(getPosition().x-1,getPosition().y);
                setTextureRect(sf::IntRect(194, 65, 62, 62));
                m_dir = Direction::Left;
            }
            if(w_gore)
            {
                setPosition(getPosition().x,getPosition().y-1);
                //setTextureRect(sf::IntRect(192, 0, 64, 64));
                setTextureRect(sf::IntRect(193, 2, 62, 62));
                m_dir = Direction::Up;
            }
            if(w_dol)
            {
                setPosition(getPosition().x,getPosition().y+1);
                setTextureRect(sf::IntRect(257, 63, 62, 62));
                m_dir = Direction::Down;
            }
            Czas.restart();

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

    void jedzenie(Owoc &element)
    {
        if(getGlobalBounds().intersects(element.getGlobalBounds()))
        {
            element.setPosition((rand()%1137), (rand()%687));
            sound.play();
            //ilosc_segmentow+=1;
            rozszerzenie();
            //cout << "segmenty: "<<get_ilosc_segmentow()<<endl;
            cout<<"segmenty: "<<m_snake.size()<<endl;

            for(size_t i=0; i<get_snake_body().size(); i++)
            {
                if(element.getGlobalBounds().intersects(m_snake[i].getGlobalBounds()))
                {
                    element.setPosition((rand()%1137), (rand()%687));
                }
            }
        }
    }

    void kolizja_cialo()
    {
        if(w_gore != 0 || w_dol != 0 || w_prawo != 0 || w_lewo != 0)
            for(size_t i=3; i<m_snake.size(); i++)
            {
                if(m_snake[i].getGlobalBounds().contains((m_snake[0].getPosition().x+m_snake[0].getGlobalBounds().width/2),(m_snake[0].getPosition().y+m_snake[0].getGlobalBounds().height/2)))
                {
                    //                cout<<"cut"<<endl;
                    for(auto j=m_snake.end(); j>=m_snake.begin()+i; j--)
                    {
                        if(j>m_snake.begin()+4)
                        {
                            m_snake.erase(j);
                            sound2.play();
                        }
                    }
                    //                cout<<"zostalo "<<m_snake.size()<<endl;
                }
            }
    }

    void set_przenikalnosc_true()
    {
        przenikalnosc=true;
    }

    void kolizja_sciana(vector<Wall*> const &sciany)
    {
        if(przenikalnosc==0)
        {
            for (auto const &el : sciany)
            {
                if(m_snake[0].getGlobalBounds().intersects(el->getGlobalBounds()))
                {
                    b_kolizja_sciana=true;
                }
            }
        }
    }

};
