#pragma once
#include "Game.h"
#include <vector>


using namespace std;

class Bullet
{
private:
	
	double damage;
	double speed;
	double xPos;
	double yPos;
	
	TextureHolder textures;
public:
	Bullet();
	void BulletRun( sf::Time TimePerFrame );
	void BordetCheck( Bullet **bullet, int i );
	double GetDamage();
	sf::Sprite spriteBullet;
};

Bullet::Bullet()
{
	speed = 800;
	damage = 300;
	textures.load(Textures::Bullet, "C:/work/Game/Game/bullet.png");
	spriteBullet.setTexture(textures.get(Textures::Bullet));
}

void Bullet::BulletRun( sf::Time TimePerFrame )
{
	sf::Vector2f movement(0.f , 0.f);
	movement.x +=speed;
	spriteBullet.move(movement * TimePerFrame.asSeconds());
}

double Bullet::GetDamage()
{
	return damage;
}