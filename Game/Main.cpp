#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "Game.h"
#include "Enemies.h"
#include "Player.h"

#include <cstdlib>
#include <ctime>
#include <cstdlib>



void main()
{
	Game game;
	Enemies enemies;
	Player player;
	srand(time(NULL));
	game.run(&enemies, &player);
}


