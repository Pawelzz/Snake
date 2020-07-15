#ifndef ELEMENTSCENY_H
#define ELEMENTSCENY_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
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


class ElementSceny : public Sprite
{
    Texture texture;

public:
    ElementSceny()
    {}
};

#endif // ELEMENTSCENY_H
