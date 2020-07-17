#ifndef GAME_H
#define GAME_H
#include "elementsceny.h"
#include "boost.h"
#include "owoc.h"
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
    Clock Time2;
    int i_time;
    sf::Font font1;
    sf::Text text1;
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
    Clock Czas3;

    bool is_flies=false;

    Clock zegar;

    void initWindow();

    void initMusic();

    void initTexture();

    void initFont();

    void initWalls();

public:

    Game();
    virtual ~Game();

    void updateSFMLEvents();

    void update();
    void render();

    void run();
};

#endif // GAME_H
