

#include "std.h"


void Enemy::AppointHP()
{
	HP = 6000;
}

Enemy::Enemy()
{
	deathTime = 0;
	speed = 150;
	xPos = (rand() % 600) + 1000.f;
	yPos = (rand() % 550) + 30.f;
	time = sf::seconds( 1.f/10000.f );
	textures.Load(Textures::Enemy, "../Game/neghvar4.png");
	ReturnSprite()->setTexture(textures.Get(Textures::Enemy));
	ReturnSprite()->setPosition(xPos, yPos);
	AppointHP();
	
}


void Enemy::MoveEnemy_Enemy( Player *player, Enemy *enemies )
{
	sf::Vector2f movement( 0.f, 0.f );
		
	if (player->GetmIsMovingLeft_Player())
		movement.x -= speed - 60.f;
	else if (player->GetmIsMovingRight_Player())
		movement.x -= speed + 60.f;
	else movement.x -= speed;

	movement.y = sin( enemies->ReturnSprite()->getPosition().x / 200 ) * 100; 
	
	ReturnSprite()->move( movement * time.asSeconds() );
}


void Enemy::SwitchBang_Enemy()
{
	if ( deathTime % 15 == 0){
		sf::IntRect IntRectangle(305 + 98 * deathTime/15 ,8, 103, 72);
		ReturnSprite()->setTextureRect( IntRectangle );
	}
	deathTime++;
}


void Enemy::DeathTime_Enemy()
{
		deathTime++;
		static sf::IntRect IntRectangle(320,15,85,58);
		ReturnSprite()->setTextureRect( IntRectangle );
}

int Enemy::GetDeathTime_Enemy()
{
	return deathTime;
}

sf::Sprite* Enemy::ReturnSprite()
{
	return &spriteEnemies;
}
