#pragma once


class GeneralQuality
{
protected: 
	int damage;
	int HP;

public:
	GeneralQuality();
	template <typename T> void LoweringHP( T *arg );
	virtual sf::Sprite* ReturnSprite() = 0;
	virtual void AppointHP() = 0;
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


