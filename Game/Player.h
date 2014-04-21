#pragma once



using namespace std;

class Player : public GeneralQuality
{
public:
	Player();
	void HandlePlayerInput_Game( sf::Keyboard::Key key, bool isPressed );
	void PlayerRun_Player();

	bool GetmIsMovingRight_Player();
	bool GetmIsMovingLeft_Player();
	
	bool GetmIsFire_Player();
	sf::Sprite* ReturnSpritePlayer();
	void FalsemIsFire_Player();
	void SetKilledEnemy_Player();
	float GetNumOfKilledEnemy_Player();
	virtual void AppointHP();
	

private:
	sf::Sprite playerPlane;
	TextureHolder textures;
	float speed;
	float killedEnemy;
	bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight, mIsFire;
	sf::Time time;

};


