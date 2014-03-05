#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemies.h"
#include "Player.h"

using namespace std;

class Game
{
public:
	Game();
	void run();
	
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render( int n );
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
	sf::RenderWindow mWindow;
	TextureHolder textures;
	
	sf::Sprite backGround;
	sf::Sprite backGroundTwo;
	
	vector<Enemy*> eneMies;
	Player plaYer;
	
	
	sf::Time TimePerFrame; 
};


Game::Game()
	: mWindow(sf::VideoMode(900, 600), "SFML Application")
	, textures()
{
	srand(time(NULL));
	
	textures.load(Textures::Landscape, "C:/work/Game/Game/Cosmos2.png");
	backGround.setTexture(textures.get(Textures::Landscape));
	backGround.setPosition(0.f,0.f);
	backGroundTwo.setTexture(textures.get(Textures::Landscape));
	backGroundTwo.setPosition(1200.f,0.f);
}

void Game::run()
{
	
	sf::Clock clock;
	
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	int timeForEneMies = 0;
	int n = 1;

	TimePerFrame = sf::seconds(1.f/10000.f);

	mWindow.setVerticalSyncEnabled(true);
	for (int i = 0; i < 3; ++i)	
		eneMies.push_back(new Enemy());		

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
		timeForEneMies = clock.getElapsedTime().asSeconds();
		render( n );
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
			plaYer.handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			plaYer.handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
		}
	}
}

void Game::update(sf::Time TimePerFrame)
{
	plaYer.PlayerRun( TimePerFrame );

	if (plaYer.ReturnmIsMovingLeft())
	{
		backGround.move(-50 * TimePerFrame.asSeconds(),0);
		backGroundTwo.move(-50 * TimePerFrame.asSeconds(),0);
		for (int i = 0; i < eneMies.size(); i++ ) 
			eneMies[i]->move(-100 * TimePerFrame.asSeconds());
	}

	else if (plaYer.ReturnmIsMovingRight())
	{
		backGround.move(-150 * TimePerFrame.asSeconds(),0);
		backGroundTwo.move(-150 * TimePerFrame.asSeconds(),0);
		for (int i = 0; i < eneMies.size(); i++ ) 
			eneMies[i]->move(-200 * TimePerFrame.asSeconds());
	}
	else{
		backGround.move(-100 * TimePerFrame.asSeconds(),0);
		backGroundTwo.move(-100 * TimePerFrame.asSeconds(),0);
		for (int i = 0; i < eneMies.size(); i++ ) 
			eneMies[i]->move(-150 * TimePerFrame.asSeconds());
	}
	if (backGround.getPosition().x <= -1150)
		backGround.setPosition(1200,0);
	if (backGroundTwo.getPosition().x <= -1150)
		backGroundTwo.setPosition(1200,0);
}


void Game::render( int n )
{
	
	mWindow.clear();
	
	mWindow.draw(backGroundTwo);
	mWindow.draw(backGround);
	mWindow.draw(plaYer.ReturnSpritePlayer());
	for ( int i = 0; i < eneMies.size(); i++ ){
		mWindow.draw(eneMies[i]->ReturnSpriteEnemies());
	}
	mWindow.display();
}


