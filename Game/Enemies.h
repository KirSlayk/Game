#pragma once
#include "TextureHolder.h"
#include "Player.h"
#include "Bullet.h"


class Enemy : public GeneralQuality
{
public:
	Enemy();
	void MoveEnemy_Enemy( Player *player, Enemy *enemies  );
	void SwitchBang_Enemy();
	void DeathTime_Enemy();
	int GetDeathTime_Enemy();
	virtual void AppointHP();
	

	sf::Sprite spriteEnemies;

private:
	
	TextureHolder textures;
	float xPos, yPos;
	float speed;
	int deathTime;
	sf::Time time;
};

