#include "Snake.h"

SnakeElement::SnakeElement(Texture txt, float x, float y)
{
    texture = txt;
    position.x = x;
    position.y = y;
    texture.loadFromFile("Textures/body.png");
    setPosition(position.x,position.y);
    texture.setSmooth(true);
    setTexture(texture);
    setScale(0.7,0.7);
}

void SnakeElement::UpdatePart()
{
    setPosition(position.x,position.y);
    setTexture(texture);
}

Snake::Snake()
{
    texture_head.loadFromFile("Textures/snake-graphics.png");
    setTexture(texture_head);
    setTextureRect(sf::IntRect(256, 0, 64, 64));
    setScale(0.7,0.7);
    setPosition(500.0, 400.0);
    m_snake.push_back(SnakeElement(texture_head,getPosition().x,getPosition().y));
    buffer.loadFromFile("Music/bite.wav");
    buffer2.loadFromFile("Music/self-bite.wav");
    sound.setBuffer(buffer);
    sound2.setBuffer(buffer2);
    for(int i = 0;i<2;i++)
    {
        rozszerzenie();
    }
}

void Snake::rozszerzenie()
{
    SnakeElement &Last = m_snake[m_snake.size()-1];
    if(m_snake.size()>1)
    {
        m_snake.push_back(SnakeElement(Last.texture,Last.position.x, Last.position.y));
    }
    else
    {
        m_snake.push_back(SnakeElement(Last.texture,Last.position.x, Last.position.y));
        m_snake[0].texture.loadFromFile("Textures/transparent.png");
        m_snake[0].setTexture(m_snake[0].texture);
        rozszerzenie();
    }
}

const SnakeElement &Snake::get_snake_head()
{
    return m_snake[0];
}

size_t Snake::get_snake_body_size()
{
    return m_snake.size();
}

int Snake::get_score()
{
    return get_ilosc_segmentow()-4;
}

int Snake::get_ilosc_segmentow()
{
    ilosc_segmentow=m_snake.size();
    return ilosc_segmentow;
}

bool Snake::get_b_kolizja_sciana()
{
    return b_kolizja_sciana;
}

const SnakeBody &Snake::get_snake_body()
{
    return m_snake;
}

void Snake::bodyanimate(Clock &Czas2)
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

void Snake::animate(Clock &Czas)
{
    b_kolizja_sciana=false;
    m_snake[0].position.x = getPosition().x;
    m_snake[0].position.y = getPosition().y;
    m_snake[0].UpdatePart();

    if(Czas.getElapsedTime().asSeconds()>0.002)
    {
        if(w_prawo)
        {
            setPosition(getPosition().x+1,getPosition().y);
            setTextureRect(sf::IntRect(255, 1, 62, 62));
        }
        if(w_lewo)
        {
            setPosition(getPosition().x-1,getPosition().y);
            setTextureRect(sf::IntRect(194, 65, 62, 62));
        }
        if(w_gore)
        {
            setPosition(getPosition().x,getPosition().y-1);
            setTextureRect(sf::IntRect(193, 2, 62, 62));
        }
        if(w_dol)
        {
            setPosition(getPosition().x,getPosition().y+1);
            setTextureRect(sf::IntRect(257, 63, 62, 62));
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
        b_kolizja_sciana=true;
    }
    if (getGlobalBounds().left+getGlobalBounds().width>1200)
    {
        b_kolizja_sciana=true;
    }
    if (getGlobalBounds().top<0)
    {
        b_kolizja_sciana=true;
    }
    if (getGlobalBounds().top+getGlobalBounds().height>700)
    {
        b_kolizja_sciana=true;
    }
}

void Snake::jedzenie(Owoc &element)
{
    if(getGlobalBounds().intersects(element.getGlobalBounds()))
    {
        element.owoc_spawn();
        sound.play();
        ilosc_segmentow+=1;
        rozszerzenie();
    }
}

void Snake::kolizja_cialo()
{
    if(w_gore != 0 || w_dol != 0 || w_prawo != 0 || w_lewo != 0)
        for(size_t i=3; i<m_snake.size(); i++)
        {
            if(m_snake[i].getGlobalBounds().contains((m_snake[0].getPosition().x+m_snake[0].getGlobalBounds().width/2),(m_snake[0].getPosition().y+m_snake[0].getGlobalBounds().height/2)))
            {
                for(auto j=m_snake.end(); j>=m_snake.begin()+i; j--)
                {
                    if(j>m_snake.begin()+4)
                    {
                        m_snake.erase(j);
                        sound2.play();
                    }
                }
            }
        }
}

void Snake::kolizja_sciana(const vector<Wall *> &sciany)
{
    for (auto const &el : sciany)
    {
        if(m_snake[0].getGlobalBounds().intersects(el->getGlobalBounds()))
        {
            b_kolizja_sciana=true;
        }
    }

}
