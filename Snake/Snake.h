#ifndef SNAKE_H
#define SNAKE_H

#endif // SNAKE_H

#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <time.h>

using namespace std;
using namespace sf;

class Stan_gry
{
    void owoc_spawn();
};

class Snake
{
    float zycie;
    float ilosc_segmentow;
    float predkosc;
    bool przenikalnosc;

public:
    Snake();
    void jedzenie();
    void kolizja_sciana();

};
