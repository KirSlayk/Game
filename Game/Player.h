#pragma once



using namespace std;

class Player
{
public:
	Player();
	void HandlePlayerInput_Game( sf::Keyboard::Key key, bool isPressed );
	void PlayerRun_Player();
	bool GetmIsMovingRight_Player();
	bool GetmIsMovingLeft_Player();
	bool GetmIsFire_Player();
	sf::Sprite ReturnSpritePlayer();
	void FalsemIsFire_Player();
	int iteratorForBullet;
	void LowingHP_Player();
	float GetHP_Player();
	void SetKilledEnemy_Player();
	float GetNumOfKilledEnemy_Player();

private:
	sf::Sprite playerPlane;
	TextureHolder textures;
	float HP;
	float speed;
	float crash;
	float killedEnemy;
	bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight, mIsFire;
	sf::Time time;
};


