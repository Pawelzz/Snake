#ifndef GAME_H
#define GAME_H
#include "elementsceny.h"
#include "boost.h"
#include "owoc.h"
#include "Snake.h"
#include "wall.h"

class Game
{
private:
    RenderWindow *window;
    Event sfEvent;

    bool is_playin=true;
    sf::Music music;
    sf::Font font;
    sf::Text text;
    Clock Time;
    int i_time;
    sf::Font font2;
    sf::Text text2;
    sf::Font font3;
    sf::Text text3;
    Texture texture_grass;
    Sprite grass;
    vector<ElementSceny*> wek;
    Snake snake;
    vector<Wall*> wektor;
    Wall table;
    Owoc fruit;
    Clock Czas;
    Clock Czas2;

    void initWindow()
    {
        this->window = new RenderWindow(sf::VideoMode(1200, 750), "Snake");
    }

    void initMusic()
    {
        music.openFromFile("arcade.wav");
        music.play();
        music.setLoop(true);
        music.setVolume(20);
    }

    void initTexture()
    {
        texture_grass.loadFromFile("grass.png");
        texture_grass.setRepeated(true);
        texture_grass.setSmooth(true);
        grass.setTexture(texture_grass);
        grass.setTextureRect(sf::IntRect(0, 0, 1200, 750));
    }

    void initFont()
    {
        font.loadFromFile("text.otf");
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::White);
        text.setPosition(0,700);
        text.setFont(font);
        font2.loadFromFile("text.otf");
        text2.setCharacterSize(40);
        text2.setFillColor(sf::Color::White);
        text2.setPosition(1000,700);
        text2.setFont(font2);
        font3.loadFromFile("text.otf");
        text3.setCharacterSize(80);
        text3.setFillColor(sf::Color::Red);
        text3.setPosition(325,300);
        text3.setFont(font3);
    }

    void initWalls()
    {
        wektor.emplace_back(new Wall(939,70));
        wektor.emplace_back(new Wall(977,70));
        wektor.emplace_back(new Wall(1015,70));
        wektor.emplace_back(new Wall(1053,70));

        wektor.emplace_back(new Wall(130,180));
        wektor.emplace_back(new Wall(130,218));
        wektor.emplace_back(new Wall(130,256));
        wektor.emplace_back(new Wall(130,294));
        wektor.emplace_back(new Wall(168,294));
        wektor.emplace_back(new Wall(206,294));
        wektor.emplace_back(new Wall(244,294));
        wektor.emplace_back(new Wall(282,294));

        wektor.emplace_back(new Wall(600,465));
        wektor.emplace_back(new Wall(600,503));
        wektor.emplace_back(new Wall(600,541));
        wektor.emplace_back(new Wall(600,579));

        wektor.emplace_back(new Wall(900,500));
        wektor.emplace_back(new Wall(938,462));
        wektor.emplace_back(new Wall(976,424));
        wektor.emplace_back(new Wall(1014,386));

        wektor.emplace_back(&table);
    }

public:



    Game()
    {
        this->initWindow();
        this->initTexture();
        this->initMusic();
        this->initWalls();
        this->initFont();
    }
    virtual ~Game()
    {
        delete this->window;
    }

    void updateSFMLEvents()
    {
        while (this->window->pollEvent(this->sfEvent))
        {
            if(this->sfEvent.type==Event::Closed)
            {
                this->window->close();
            }
//            if (this->sfEvent.type == sf::Event::KeyPressed)
//            {
//                if (this->sfEvent.key.code == sf::Keyboard::Up || this->sfEvent.key.code == sf::Keyboard::Down || this->sfEvent.key.code == sf::Keyboard::Left || this->sfEvent.key.code == sf::Keyboard::Right )
//                {
//                    is_playin=true;
//                }
//            }

        }
    }
    void update()
    {
        this->updateSFMLEvents();
    }
    void render()
    {
        this->window->clear();

        snake.kolizja_cialo();
        snake.jedzenie(fruit);
        snake.animate(Czas);
        snake.bodyanimate(Czas2);
        snake.kolizja_sciana(wektor);

        i_time=Time.getElapsedTime().asSeconds();

        text.setString("Time: "+to_string(i_time)+"s");

        text2.setString("Score: "+to_string((snake.get_score())));

        // clear the window with black color
        this->window->clear(sf::Color::Black);

        // draw everything here...

        this->window->draw(grass);
        for(size_t i=0;i<snake.m_snake.size()-1;i++)
        {
            this->window->draw(snake.m_snake[i]);
        }
        this->window->draw(snake);

        this->window->draw(fruit);

        for (auto &el : wektor)
        {
            fruit.owoc_resp(*el);
            this->window->draw(*el);
        }


        this->window->draw(text);
        this->window->draw(text2);



        if(snake.get_b_kolizja_sciana()==1)
        {
            is_playin=false;
            text3.setString("GAME OVER :c");
            this->window->draw(text3);
            music.stop();
        }



        this->window->display();
    }

    void run()
    {
        while (this->window->isOpen())
        {
            this->update();

            if(is_playin==1)
            {
                this->render();
            }

        }
    }

};

#endif // GAME_H
