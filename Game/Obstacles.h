#pragma once

class Obstacle : public Object
{
public: 
	Obstacle();
	void ObstacleMove_Obstacle();
	virtual sf::Sprite* ReturnSprite();
	void BorderCheck_Obstacle();
private:
	sf::Time mTime;
	int x, y;
};

