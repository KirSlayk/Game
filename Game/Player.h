#pragma once
#include "Bullet.h"

using namespace std;

class Player
{
private:
	sf::Sprite playerPlane;
	TextureHolder textures;
	double strength;
	double HP;
	double speed;
	bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight, mIsFire;

public:
	Player();
	void handlePlayerInput( sf::Keyboard::Key key, bool isPressed );
	void PlayerRun( sf::Time TimePerFrame );
	bool ReturnmIsMovingRight();
	bool ReturnmIsMovingLeft();
	bool GetmIsFire();
	sf::Sprite ReturnSpritePlayer();
	void FalsemIsFire();
	int iteratorForBullet;
	
	
};


Player::Player()
{
	mIsMovingUp = mIsMovingDown = mIsMovingLeft = mIsMovingRight = mIsFire = false;
	speed = 250;
	HP = 10000;
	strength = 50;
	textures.load(Textures::Airplane, "C:/work/Game/Game/alienblaster.png");
	playerPlane.setTexture(textures.get(Textures::Airplane));
	playerPlane.setPosition(0.f, 250.f);
	iteratorForBullet = -1;
}

sf::Sprite Player:: ReturnSpritePlayer()
{
	return playerPlane;
}

void Player::FalsemIsFire()
{
	mIsFire = false;
}
void Player::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
	else if (key == sf::Keyboard::F)
		mIsFire = isPressed;
	
}

void Player::PlayerRun( sf::Time TimePerFrame )
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
	
	playerPlane.move(movement * TimePerFrame.asSeconds());
	
}

bool Player::ReturnmIsMovingRight()
{
	return mIsMovingRight;
}

bool Player::ReturnmIsMovingLeft()
{
	return mIsMovingLeft;
}

bool Player::GetmIsFire()
{
	return mIsFire;
}