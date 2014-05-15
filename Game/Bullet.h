#pragma once

//using namespace std;

class Bullet
{
public:
	Bullet();
	void BulletRun_Bullet();
	sf::Sprite* ReturnSprite();

private:
	sf::Sprite spriteBullet;
	float speed;
	float xPos;
	float yPos;
	sf::Time time;
	TextureHolder textures;
};

