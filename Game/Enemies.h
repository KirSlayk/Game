#pragma once
#include <cmath>
#include "TextureHolder.h"

class Enemies
{
private:
	TextureHolder textures;
	double xPos, yPos;
	int speed;
public:
	Enemies();
	void Enem( Enemies *enem);
	void move(double time);
	sf::Sprite spriteEnemies;
	Enemies *prev;
	Enemies *next;
};




Enemies::Enemies()
	: spriteEnemies()
	, textures()
{
	speed = 100;
	xPos = (rand() % 60) + 800;
	yPos = (rand() % 550) + 1;
	textures.load(Textures::Enemies, "C:/work/Game/Game/neghvar4.png");
	spriteEnemies.setTexture(textures.get(Textures::Enemies));
	spriteEnemies.setPosition(xPos, yPos);
}

void Enemies::move(double time)
{
	//sf::Vector2f movementEnemies(0.f, 0.f);
	//movementEnemies.x-= ( time / speed  );
	spriteEnemies.move(time,0);
}