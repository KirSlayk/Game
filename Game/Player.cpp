

#include "std.h"

Player::Player()
{
	mIsMovingUp = false;
	mIsMovingDown = false;
	mIsMovingLeft = false;
	mIsMovingRight = false;
	mIsFire = false;
	speed = 250;
	HP = 10000;
	strength = 50;
	textures.Load(Textures::Airplane, "../Game/alienblaster.png");
	playerPlane.setTexture(textures.Get(Textures::Airplane));
	playerPlane.setPosition(0.f, 250.f);
	iteratorForBullet = -1;
	time = sf::seconds(1.f/10000.f);
}

sf::Sprite Player:: ReturnSpritePlayer()
{
	return playerPlane;
}

void Player::FalsemIsFire_Player()
{
	mIsFire = false;
}
void Player::HandlePlayerInput_Game(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
	if (key == sf::Keyboard::F)
		mIsFire = isPressed;
	
}

void Player::PlayerRun_Player()
{
	sf::Vector2f movement(0.f, 0.f);
	
	if (mIsMovingUp)
		movement.y -= speed;
	if (mIsMovingDown)
		movement.y += speed;
	if (mIsMovingLeft)
		movement.x -= speed;
	if (mIsMovingRight)
		movement.x += speed;
	
	playerPlane.move(movement * time.asSeconds());
	
}

bool Player::ReturnmIsMovingRight_Player()
{
	return mIsMovingRight;
}

bool Player::ReturnmIsMovingLeft_Player()
{
	return mIsMovingLeft;
}

bool Player::GetmIsFire_Player()
{
	return mIsFire;
}