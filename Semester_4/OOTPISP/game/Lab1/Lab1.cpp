#include <SFML/Graphics.hpp>
#include <time.h>
#include "DisplaysObject.h"
#include "Game.h"
#include "CommonResource.h"
using namespace sf;

int main()
{
    CommonResource::initialize();
    Game::start();
    return 0;
}
