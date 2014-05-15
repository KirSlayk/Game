#pragma once
#include "TextureHolder.h"
#include "Player.h"
#include "Bullet.h"


class Enemy : public Object
{
public:
	Enemy();
	void MoveEnemy_Enemy( Player *player, Enemy *enemies  );
	void SwitchBang_Enemy();
	void DeathTime_Enemy();
	int GetDeathTime_Enemy();
	virtual sf::Sprite* ReturnSprite();

private:
	int deathTime;
	sf::Time time;	
};

