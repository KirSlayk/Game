#pragma once


class GeneralQuality
{
protected: 
	int damage;
	int HP;

public:
	GeneralQuality();
	//GeneralQuality( int _damage );
	template <typename T> void LoweringHP( T *arg );
	//template <typename sf::Sprite> sf::Sprite* ReturnSprite();
	virtual void AppointHP() {};
	virtual int GetHP();
};


template <typename T> void GeneralQuality::LoweringHP( T* arg )
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

//template <typename sf::Sprite> sf::Sprite* GeneralQuality::ReturnSprite()
//{
	//return &sf::Sprite;
//}

