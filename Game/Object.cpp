#include "std.h"



Object::Object()
{
	damage = 0;
	HP = 0;
	speed = 0;
}

Object::Object( int damage, int HP, float speed )
{
	this->HP = HP;
	this->damage = damage;
	this->speed = speed;
}

int Object::GetHP()
{
	return HP;
}


