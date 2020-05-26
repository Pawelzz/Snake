#include "Snake.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(1200, 750), "Snake");

    // create some shapes

    Texture texture_grass;
    if(!texture_grass.loadFromFile("grass.png")) { return 1; }
    texture_grass.setRepeated(true);
    texture_grass.setSmooth(true);
    Sprite grass;
    grass.setTexture(texture_grass);
    grass.setTextureRect(sf::IntRect(0, 0, 1200, 750));

    Texture texture_snake;
    if(!texture_snake.loadFromFile("snake-graphics.png")) { return 1; }
    texture_snake.setRepeated(true);
    texture_snake.setSmooth(true);
    Sprite snake;
    snake.setTexture(texture_snake);
//    snake.setTextureRect(sf::IntRect(256, 0, 64, 64));

//    sf::RectangleShape rectangle(sf::Vector2f(30, 30));
    snake.setPosition(500.0, 400.0);
//    rectangle.setFillColor(sf::Color(100, 50, 250));

    bool w_gore=0;
    bool w_dol=0;
    bool w_prawo=1;
    bool w_lewo=0;

    float pozycja_x = snake.getPosition().x;
    float pozycja_y = snake.getPosition().y;

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        pozycja_x = snake.getPosition().x;
        pozycja_y = snake.getPosition().y;

        if(w_prawo)
        {
            snake.setPosition(pozycja_x+0.2,pozycja_y);
            snake.setTextureRect(sf::IntRect(256, 0, 64, 64));
        }
        if(w_lewo)
        {
            snake.setPosition(pozycja_x-0.2,pozycja_y);
            snake.setTextureRect(sf::IntRect(192, 64, 64, 64));
        }
        if(w_gore)
        {
            snake.setPosition(pozycja_x,pozycja_y-0.2);
            snake.setTextureRect(sf::IntRect(192, 0, 64, 64));
        }
        if(w_dol)
        {
            snake.setPosition(pozycja_x,pozycja_y+0.2);
            snake.setTextureRect(sf::IntRect(256, 64, 64, 64));
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

        if (snake.getGlobalBounds().left<0)
        {
            snake.setPosition(600,350);
        }
        if (snake.getGlobalBounds().left+snake.getGlobalBounds().width>1200)
        {
            snake.setPosition(600,350);
        }
        if (snake.getGlobalBounds().top<0)
        {
            snake.setPosition(600,350);
        }
        if (snake.getGlobalBounds().top+snake.getGlobalBounds().height>750)
        {
            snake.setPosition(600,350);
        }

//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && w_gore==1)
//        {
//            w_gore=0;
//            w_lewo=1;
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && w_dol==1)
//        {
//            w_dol=0;
//            w_lewo=1;
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && w_lewo==1)
//        {
//            w_lewo=0;
//            w_dol=1;
//        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...

        window.draw(grass);
        window.draw(snake);

        // end the current frame
        window.display();
    }

    return 0;
}
