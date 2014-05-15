#pragma once



using namespace std;

class Player : public Object
{
public:
	Player();
	void HandlePlayerInput_Game( sf::Keyboard::Key key, bool isPressed );
	void PlayerRun_Player();
	bool GetmIsMovingRight_Player();
	bool GetmIsMovingLeft_Player();
	bool GetmIsFire_Player();
	void FalsemIsFire_Player();
	void SetKilledEnemy_Player();
	float GetNumOfKilledEnemy_Player();
	virtual sf::Sprite* ReturnSprite();
	

private:
	float killedEnemy;
	bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight, mIsFire;
	sf::Time time;
};


