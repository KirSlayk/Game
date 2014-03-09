#pragma once
#include "TextureHolder.h"
#include "Player.h"
#include "Bullet.h"


class Enemy
{
public:
	Enemy();
	void MoveEnemy_Enemy( Player *player );
	void LoweringHP_Enemy( Bullet *bullet );
	float GetHP_Enemy();
	void SwitchBang_Enemy();
	void DeathTime_Enemy();
	int GetDeathTime_Enemy();

	sf::Sprite spriteEnemies;

private:
	
	TextureHolder textures;
	float xPos, yPos;
	float speed;
	int deathTime;
	float HP;
	sf::Time time;
};

