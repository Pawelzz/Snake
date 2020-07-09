#include "Snake.h"
#include "elementsceny.h"
#include "owoc.h"
#include "list"

using namespace std;
using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 750), "Snake");

    srand( time( NULL ) );

    Texture texture_grass;
    if(!texture_grass.loadFromFile("grass.png")) { return 1; }
    texture_grass.setRepeated(true);
    texture_grass.setSmooth(true);
    Sprite grass;
    grass.setTexture(texture_grass);
    grass.setTextureRect(sf::IntRect(0, 0, 1200, 750));

    Snake snake;

    Owoc fruit;
    Clock Czas;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        snake.jedzenie(fruit);

        snake.animate();
        snake.bodyanimate(Czas);

//        for(int i=100; i>0; i--)
//        {
//            snake[i].pos_x=snake[i-1].pos_x;
//            snake[i].pos_y=snake[i-1].pos_y;
//        }





        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...

        window.draw(grass);
        window.draw(snake);
        for(int i=0;i<snake.m_snake.size()-1;i++)
        {
            window.draw(snake.m_snake[i]);
        }
        //cout<<snake.m_snake.size()-1<<endl;
        window.draw(fruit);

        // end the current frame
        window.display();
    }

    return 0;
}
