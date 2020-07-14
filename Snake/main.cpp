#include "Snake.h"
#include "elementsceny.h"
#include "owoc.h"
#include "wall.h"
#include "boost.h"

using namespace std;
using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 750), "Snake");

    srand( time( NULL ) );

    int z=1;

    sf::Music music;
    if (!music.openFromFile("arcade.wav"))
        return -1; // error
    music.play();
    music.setLoop(true);
    music.setVolume(20);

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    Clock Time;
    int i_time;
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::Black);
    text.setPosition(0,700);
    text.setFont(font);

    sf::Font font2;
    font2.loadFromFile("arial.ttf");
    sf::Text text2;
    text2.setCharacterSize(40);
    text2.setFillColor(sf::Color::Black);
    text2.setPosition(1050,700);
    text2.setFont(font2);

    sf::Font font3;
    font3.loadFromFile("arial.ttf");
    sf::Text text3;
    text3.setCharacterSize(80);
    text3.setFillColor(sf::Color::Red);
    text3.setPosition(350,300);
    text3.setFont(font3);


    Texture texture_grass;
    if(!texture_grass.loadFromFile("grass.png")) { return 1; }
    texture_grass.setRepeated(true);
    texture_grass.setSmooth(true);
    Sprite grass;
    grass.setTexture(texture_grass);
    grass.setTextureRect(sf::IntRect(0, 0, 1200, 750));

    vector<ElementSceny*> wek;

    Snake snake;

    vector<Wall*> wektor;

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

    Wall table;

    wektor.emplace_back(&table);


    Owoc fruit;
    Owoc point(z);
    Clock Czas;
    Clock Czas2;
    Clock Czas3;
    //    Boost slow(Czas3);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        snake.kolizja_cialo();

        snake.jedzenie(fruit);
        //        slow.resp(Czas3);





        snake.animate(Czas);
        snake.bodyanimate(Czas2);



        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...

        window.draw(grass);
        for(size_t i=0;i<snake.m_snake.size()-1;i++)
        {
            window.draw(snake.m_snake[i]);
        }
        window.draw(snake);

        window.draw(fruit);

        for (auto &el : wektor)
        {
            fruit.owoc_resp(*el);
            window.draw(*el);
        }


        snake.kolizja_sciana(wektor);

        if(snake.get_b_kolizja_sciana()==1)
        {
//            cout<<"Uderzyles w sciane!"<<endl<<"GAME OVER"<<endl;
            text3.setString("GAME OVER :c");
            window.draw(text3);

        }
        i_time=Time.getElapsedTime().asSeconds();
        text.setString("Time: "+to_string(i_time)+"s");

        text2.setString(to_string((snake.get_score())));
        window.draw(table);

        window.draw(text);
        window.draw(text2);

        window.draw(point);





        //        window.draw(slow);

        // end the current frame
        window.display();
    }

    return 0;
}
