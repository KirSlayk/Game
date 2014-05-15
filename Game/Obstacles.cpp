#include "std.h"

Obstacle::Obstacle()
{
	srand(time(NULL));
	textures.Load(Textures::Obstancle, "../Game/comet sprite.png");
	sprite.setTexture(textures.Get(Textures::Obstancle));
	speed = 135;
	HP = 10000;
	damage = 10000;
	mTime  = sf::seconds( 1.f/10000.f );
	x = rand()%2000+1500;
	y = rand()%500;
	sprite.setPosition( x, y );
}


void Obstacle::ObstacleMove_Obstacle()
{
	sf::Vector2f movement(0.f , 0.f);
	movement.x -=speed;
	sprite.move(movement * mTime.asSeconds());
}

sf::Sprite* Obstacle::ReturnSprite()
{
	return &sprite;
}


void Obstacle::BorderCheck_Obstacle()
{
	if ( sprite.getPosition().x < -100 )
		sprite.setPosition( rand()%10000+2000, rand()%500 );
}