

#include "std.h"


Bullet::Bullet()
{
	speed = 800;
	textures.Load(Textures::Bullet, "../Game/bullet.png");
	ReturnSprite()->setTexture(textures.Get(Textures::Bullet));
	time  = sf::seconds( 1.f/10000.f );
}

void Bullet::BulletRun_Bullet()
{
	sf::Vector2f movement(0.f , 0.f);
	movement.x +=speed;
	ReturnSprite()->move(movement * time.asSeconds());
}

sf::Sprite* Bullet::ReturnSprite()
{
	return &spriteBullet;
}
