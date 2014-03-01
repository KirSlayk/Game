#pragma once




class Player
{
private:
	sf::Sprite playerPlane;
	TextureHolder textures;
	double strength;
	double HP;
	double speed;
	bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight;

public:
	Player();
	void handlePlayerInput( sf::Keyboard::Key key, bool isPressed );
	void PlayerRun( sf::Time TimePerFrame );
	sf::Sprite ReturnSpritePlayer();
	
	
	
};


Player::Player()
	: playerPlane()
	, textures()
{
	mIsMovingUp = mIsMovingDown = mIsMovingLeft = mIsMovingRight = false;
	speed = 250;
	HP = 100;
	strength = 50;
	textures.load(Textures::Airplane, "C:/work/Game/Game/alienblaster.png");
	playerPlane.setTexture(textures.get(Textures::Airplane));
	playerPlane.setPosition(0.f, 250.f);
}

sf::Sprite Player:: ReturnSpritePlayer()
{
	return playerPlane;
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