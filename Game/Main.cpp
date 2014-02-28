#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "ClassGame.h"
#include "ClassEnemies.h"
#include "ctime"
#include <cstdlib>


void main()
{
	Game game;
	srand(time(NULL));
	game.run();
}


