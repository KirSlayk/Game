#pragma once
#include <SFML/Graphics.hpp>
#include "Enemies.h"
#include "Player.h"


class Game
{
public:
	Game();
	void run(Enemies *enemies, Player *player);
	
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
	sf::RenderWindow mWindow;
	TextureHolder textures;
	
	sf::Sprite backGround;
	sf::Sprite backGroundTwo;
	
	
	Enemies *eneMies;
	Player *plaYer;
	
	sf::Time TimePerFrame; 

	
};

Game::Game()
	: mWindow(sf::VideoMode(900, 600), "SFML Application")
	, textures()
{
	srand(time(NULL));
	
	textures.load(Textures::Landscape, "C:/work/Game/Game/Cosmos2.png");
	backGround.setTexture(textures.get(Textures::Landscape));
	backGround.setPosition(1200.f,0.f);
	textures.load(Textures::LandscapeTwo, "C:/work/Game/Game/Cosmos2.png");
	backGroundTwo.setTexture(textures.get(Textures::LandscapeTwo));
	backGroundTwo.setPosition(0.f,0.f);
}

void Game::run(Enemies *enemies, Player *player)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	TimePerFrame = sf::seconds(1.f/60.f);

	eneMies = enemies;
	plaYer = player;

	
	mWindow.setVerticalSyncEnabled(true);
	
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			eneMies->move(0);
			update(TimePerFrame);
		}
		
		render();
	}
}


void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::KeyPressed:
			plaYer->handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			plaYer->handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
		}
	}
}

void Game::update(sf::Time TimePerFrame)
{
	plaYer->PlayerRun( TimePerFrame );

	backGround.move(-1,0);
	backGroundTwo.move(-1,0);
	if (backGround.getPosition().x == 3)
		backGroundTwo.setPosition(1200,0);
	if (backGroundTwo.getPosition().x == 3)
		backGround.setPosition(1200,0);
}

void Game::render()
{
	mWindow.clear();
	
	mWindow.draw(backGroundTwo);
	mWindow.draw(backGround);
	mWindow.draw(plaYer->ReturnSpritePlayer());
	mWindow.draw(eneMies->spriteEnemies);
	mWindow.display();
}
