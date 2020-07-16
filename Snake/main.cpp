#include "game.h"

using namespace std;
using namespace sf;


int main()
{
    srand( time( NULL ) );

    Game game;

    game.run();

    return 0;
}
