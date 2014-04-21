#pragma once

using namespace std;

class Bullet
{
public:
	Bullet();
	void BulletRun_Bullet();
	float GetDamage_Bullet(); //
	sf::Sprite spriteBullet;

private:
	
	float damage;
	float speed;
	float xPos;
	float yPos;
	sf::Time time;
	
	TextureHolder textures;
};

