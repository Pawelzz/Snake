#ifndef OWOC_H
#define OWOC_H
#include "elementsceny.h"
#include "wall.h"


class Owoc :public ElementSceny
{
private:
    Texture texture;
public:
    Owoc();

    void owoc_spawn();

    void owoc_resp(Wall const &el);
};

#endif // OWOC_H
