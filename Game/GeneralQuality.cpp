#include "std.h"



GeneralQuality::GeneralQuality()
{
	damage = 0;
	HP = 0;
	speed = 0;
}

GeneralQuality::GeneralQuality( int damage, int HP, float speed )
{
	this->HP = HP;
	this->damage = damage;
	this->speed = speed;
}

int GeneralQuality::GetHP()
{
	return HP;
}


