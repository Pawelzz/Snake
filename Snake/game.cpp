#include "game.h"

void Game::initWindow()
{
    this->window = new RenderWindow(sf::VideoMode(1200, 750), "Snake");
}

void Game::initMusic()
{
    music.openFromFile("Music/arcade.wav");
    music.play();
    music.setLoop(true);
    music.setVolume(20);
}

void Game::initTexture()
{
    texture_grass.loadFromFile("Textures/grass.png");
    texture_grass.setRepeated(true);
    texture_grass.setSmooth(true);
    grass.setTexture(texture_grass);
    grass.setTextureRect(sf::IntRect(0, 0, 1200, 750));
}

void Game::initFont()
{
    font.loadFromFile("Fonts/text.otf");
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setPosition(0,700);
    text.setFont(font);
    text2.setCharacterSize(40);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(1000,700);
    text2.setFont(font);
    text3.setCharacterSize(80);
    text3.setFillColor(sf::Color::Red);
    text3.setPosition(325,300);
    text3.setFont(font);
}

void Game::initWalls()
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

Game::Game()
{
    this->initWindow();
    this->initTexture();
    this->initMusic();
    this->initWalls();
    this->initFont();
}

Game::~Game()
{
    delete this->window;
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if(this->sfEvent.type==Event::Closed)
        {
            this->window->close();
        }
        if (this->sfEvent.type == sf::Event::KeyPressed)
        {
            if (this->sfEvent.key.code == sf::Keyboard::Left || this->sfEvent.key.code == sf::Keyboard::Right ||
                    this->sfEvent.key.code == sf::Keyboard::Up || this->sfEvent.key.code == sf::Keyboard::Down)
            {
                is_flies=true;
            }
        }
    }
}

void Game::update()
{
    this->updateSFMLEvents();
}

void Game::render()
{
    this->window->clear();

    snake.kolizja_cialo();
    snake.jedzenie(fruit);
    snake.animate(Czas);
    snake.bodyanimate(Czas2);
    snake.kolizja_sciana(wektor);

    if (is_flies==false)
    {
        Time.restart();
        Czas3.restart();
    }

    i_time=Time.getElapsedTime().asSeconds();

    text.setString("Time: "+to_string(i_time)+"s");

    text2.setString("Score: "+to_string((snake.get_score())));

    this->window->clear(sf::Color::Black);

    this->window->draw(grass);
    for(size_t i=0;i<snake.get_snake_body_size()-1;i++)
    {
        this->window->draw(snake.get_snake_body()[i]);
    }
    this->window->draw(snake);

    this->window->draw(fruit);

    for (auto &el : wektor)
    {
        fruit.owoc_resp(*el);
        this->window->draw(*el);
    }

    this->window->draw(text);
    this->window->draw(text1);
    this->window->draw(text2);

    if(snake.get_b_kolizja_sciana()==1)
    {
        is_playin=false;
        text3.setString("GAME OVER");
        this->window->draw(text3);
        music.stop();
    }
    this->window->display();
}

void Game::run()
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
