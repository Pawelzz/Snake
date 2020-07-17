#ifndef SNAKE_H
#define SNAKE_H
#include "elementsceny.h"
#include "owoc.h"
#include "wall.h"

#endif // SNAKE_H

struct SnakeElement :public ElementSceny
{
    Texture texture;
    Vector2f position;
    SnakeElement(Texture txt, float x, float y);
    void UpdatePart();
};

using SnakeBody = vector<SnakeElement>;

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

    bool w_gore=0;
    bool w_dol=0;
    bool w_prawo=0;
    bool w_lewo=0;

    SnakeBody m_snake;

public:


    Snake();

    void rozszerzenie();

    SnakeElement const& get_snake_head();

    size_t get_snake_body_size();

    int get_score();

    int get_ilosc_segmentow();

    bool get_b_kolizja_sciana();

    SnakeBody const& get_snake_body();

    void bodyanimate(Clock &Czas2);

    void animate(Clock &Czas);

    void jedzenie(Owoc &element);

    void kolizja_cialo();

    void kolizja_sciana(vector<Wall*> const &sciany);

};
