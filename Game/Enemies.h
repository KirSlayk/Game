#pragma once
#include <cmath>
#include "TextureHolder.h"

class Enemy
{
private:
	TextureHolder textures;
	double xPos, yPos;
	int speed;
	sf::Sprite spriteEnemies;

public:
	Enemy();
	void move(double time);
	sf::Sprite ReturnSpriteEnemies();
};

Enemy::Enemy()
{
	speed = 100;
	xPos = (rand() % 60) + 800;
	yPos = (rand() % 550) + 1;
	textures.load(Textures::Enemy, "C:/work/Game/Game/neghvar4.png");
	spriteEnemies.setTexture(textures.get(Textures::Enemy));
	spriteEnemies.setPosition(xPos, yPos);
}

void Enemy::move(double time)
{
	spriteEnemies.move(time,0);
}

sf::Sprite Enemy::ReturnSpriteEnemies()
{
	return spriteEnemies;
}
