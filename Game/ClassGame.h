#pragma once
#include "iostream"
#include <SFML/Graphics.hpp>
#include "ClassEnemies.h"
#include <ctime>
#include <cstdlib>


class Game
{
public:
	Game();
	void run();
	bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight;
	int speed;
	double Time;
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
	sf::RenderWindow mWindow;
	TextureHolder textures;
	
	sf::Sprite background;
	sf::Sprite playerPlane;
	sf::Sprite spriteEnemies;
	
	Enemies *enemies;
	
	sf::Time TimePerFrame; 

	
};

Game::Game()
	: mWindow(sf::VideoMode(900, 600), "SFML Application")
	, playerPlane()
	, textures()
{
	srand(time(NULL));
	speed = 150;
	Time = 0;
	textures.load(Textures::Airplane, "C:/work/Game/Game/alienblaster.png");
	playerPlane.setTexture(textures.get(Textures::Airplane));
	playerPlane.setPosition(450.f, 500.f);
	textures.load(Textures::Landscape, "C:/work/Game/Game/Cosmos.png");
	background.setTexture(textures.get(Textures::Landscape));
	background.setPosition(0.f,0.f);
	textures.load(Textures::Enemies, "C:/work/Game/Game/neghvar3.png");
	spriteEnemies.setTexture(textures.get(Textures::Enemies));
	spriteEnemies.setPosition(rand()%100+700.f, rand()%500+1.f);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	Time = clock.getElapsedTime().asMicroseconds() / 300;
	TimePerFrame = sf::seconds(1.f/60.f);
	mWindow.setVerticalSyncEnabled(true);
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
		}
	}
}

void Game::update(sf::Time TimePerFrame)
{
	sf::Vector2f movement(0.f, 0.f);
	sf::Vector2f movementEnemies(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= speed;
	if (mIsMovingDown)
		movement.y += speed;
	if (mIsMovingLeft)
		movement.x -= speed;
	if (mIsMovingRight)
		movement.x += speed;
	playerPlane.move(movement * TimePerFrame.asSeconds());
	spriteEnemies.move(-1 , 0 ); 
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(background);
	mWindow.draw(playerPlane);
	mWindow.draw(spriteEnemies);
	
	mWindow.display();
}
