#pragma once



using namespace std;

class Player
{
public:
	Player();
	void HandlePlayerInput_Game( sf::Keyboard::Key key, bool isPressed );
	void PlayerRun_Player();
	bool ReturnmIsMovingRight_Player();
	bool ReturnmIsMovingLeft_Player();
	bool GetmIsFire_Player();
	sf::Sprite ReturnSpritePlayer();
	void FalsemIsFire_Player();
	int iteratorForBullet;

private:
	sf::Sprite playerPlane;
	TextureHolder textures;
	float strength;
	float HP;
	float speed;
	bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight, mIsFire;
	sf::Time time;
};


