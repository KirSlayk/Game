#pragma once
#include <cmath>
#include "TextureHolder.h"
#include "Bullet.h"

class Enemy
{
private:
	TextureHolder textures;
	double xPos, yPos;
	int speed;
	
	double HP;

public:
	sf::Sprite spriteEnemies;
	Enemy();
	void move(double time);
	void LoweringHP( Bullet *bullet );
	double GetHP();
	sf::Sprite ReturnSpriteEnemies();
};

Enemy::Enemy()
{
	speed = 100;
	HP = 1200;
	xPos = (rand() % 60) + 1000;
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


void Enemy::LoweringHP( Bullet *bullet )
{
	HP -= bullet->GetDamage();
}

double Enemy::GetHP()
{
	return HP;
}