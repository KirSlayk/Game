#pragma once
#include <cmath>
#include "TextureHolder.h"
#include "Bullet.h"
#include "Player.h"



class Enemy
{
private:
	
	TextureHolder textures;
	double xPos, yPos;
	float speed;
	int deathTime;
	int HP;
	sf::Time time;
	

public:
	sf::Sprite spriteEnemies;
	Enemy();
	void moveEnemy( Player *player );
	void LoweringHP( Bullet *bullet );
	int GetHP();
	void SwitchBang();
	void DeathTime();
	int GetDeathTime();
	

	
};

Enemy::Enemy()
{
	deathTime = 0;
	speed = 150;
	HP = 1200;
	xPos = (rand() % 60) + 1000;
	yPos = (rand() % 550) + 1;
	time = sf::seconds( 1.f/10000.f );
	textures.load(Textures::Enemy, "C:/work/Game/Game/neghvar4.png");
	spriteEnemies.setTexture(textures.get(Textures::Enemy));
	spriteEnemies.setPosition(xPos, yPos);
	
}


void Enemy::moveEnemy( Player *player )
{
	sf::Vector2f movement( 0.f, 0.f );
		
	if (player->ReturnmIsMovingLeft())
		movement.x -= speed - 60.f;
	else if (player->ReturnmIsMovingRight())
		movement.x -= speed + 60.f;
	else movement.x -= speed;
	
	
	

	spriteEnemies.move( movement * time.asSeconds() );
}

void Enemy::LoweringHP( Bullet *bullet )
{
	HP -= bullet->GetDamage();
}

void Enemy::SwitchBang()
{
	if ( deathTime % 15 == 0){
		sf::IntRect IntRectangle(305 + 98 * deathTime/15 ,8, 103, 72);
		spriteEnemies.setTextureRect( IntRectangle );
	}
	deathTime++;
}

int Enemy::GetHP()
{
	return HP;
}

void Enemy::DeathTime()
{
		deathTime++;
		static sf::IntRect IntRectangle(320,15,85,58);
		spriteEnemies.setTextureRect( IntRectangle );
}

int Enemy::GetDeathTime()
{
	return deathTime;
}

