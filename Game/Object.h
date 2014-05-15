#pragma once


class Object
{
protected: 
	int damage;
	int HP;
	float speed;
	TextureHolder textures;
	sf::Sprite sprite;

public:
	Object();
	Object( int damage, int HP, float speed );
	template <typename T> void LoweringHP( T *arg );
	virtual sf::Sprite* ReturnSprite() = 0;
	virtual int GetHP();
};


template <typename T> void Object::LoweringHP( T* arg )
{
	if (dynamic_cast<Player*>(arg))
	{
		HP -= 5 * damage;		
	}

	else if (dynamic_cast<Enemy*>(arg))
	{
		HP -= 2 * damage;
	}

}