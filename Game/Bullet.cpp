#pragma once

#include "std.h"


Bullet::Bullet()
{
	speed = 800;
	damage = 300;
	textures.Load(Textures::Bullet, "../Game/bullet.png");
	spriteBullet.setTexture(textures.Get(Textures::Bullet));
	time  = sf::seconds( 1.f/10000.f );
}

void Bullet::BulletRun_Bullet()
{
	sf::Vector2f movement(0.f , 0.f);
	movement.x +=speed;
	spriteBullet.move(movement * time.asSeconds());
}

float Bullet::GetDamage_Bullet()
{
	return damage;
}