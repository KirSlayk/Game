#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

class Enemies
{
private:
	
	int speed;
public:
	Enemies();
	void move(double time);
	
	double xPos, yPos;
};

Enemies::Enemies()
{
	speed = 100;
	xPos = (rand() % (-39)) + 10;
	yPos = (rand() % (-39)) + 10;
	
}

void Enemies::move(double time)
{
	yPos += ( time / speed * 100 );
}