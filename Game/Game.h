#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemies.h"
#include "Player.h"
#include "Bullet.h"

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
	void runWorld();
	void collision();
	void shoting();
	void borderCheck();
private:
	sf::RenderWindow mWindow;
	TextureHolder textures;
	
	sf::Sprite backGround;
	sf::Sprite backGroundTwo;
	
	vector<Enemy*> eneMies;
	Player plaYer;
	vector<Bullet*> bulLet;
	
	
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
	

	while (mWindow.isOpen())
	{
		if ( timeForEneMies ){
			n = timeForEneMies % 3;
			if (eneMies.size() < 10 ) 
				for (int i = 0; i < n - 1; ++i)	
					eneMies.push_back(new Enemy());		
		}

		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		
		shoting();
		borderCheck();
		collision();

		timeForEneMies = clock.getElapsedTime().asMilliseconds() / 5 ;
		render( n );
	}
}

void Game::shoting()
{
	if ( plaYer.GetmIsFire() ){
		plaYer.iteratorForBullet++;
		for ( int i = plaYer.iteratorForBullet; i <= plaYer.iteratorForBullet; i++ ){
			bulLet.push_back(new Bullet());
			bulLet[ i ]->spriteBullet.setPosition(plaYer.ReturnSpritePlayer().getPosition().x + 65, plaYer.ReturnSpritePlayer().getPosition().y + 30);
			plaYer.FalsemIsFire();		
		}	
	}
}

void Game::borderCheck()
{
	for ( int i = 0; i < bulLet.size(); i++ ){
		vector<Bullet*>::iterator itera = bulLet.begin();
			if ( bulLet[i]->spriteBullet.getPosition().x > 900 ){
				bulLet.erase( itera );
				plaYer.iteratorForBullet--;
			}
	}
	for ( int i = 0; i < eneMies.size(); i++ ){
		vector<Enemy*>::iterator iterator = eneMies.begin();
		if ( eneMies.size() )
			if ( eneMies[i]->spriteEnemies.getPosition().x < -100 ){
				eneMies.erase( iterator + i );
				}	
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
	
	if ( plaYer.iteratorForBullet >= 0 )
		for ( int i = 0; i <= plaYer.iteratorForBullet; i++ ){
			bulLet[i]->BulletRun( TimePerFrame );
		}
	
	runWorld();

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

	for ( int i = 0; i < bulLet.size(); i++ )
		mWindow.draw(bulLet[i]->spriteBullet);
	mWindow.draw(plaYer.ReturnSpritePlayer());
	for ( int i = 0; i < eneMies.size(); i++ ){
		mWindow.draw(eneMies[i]->ReturnSpriteEnemies());
	}
	mWindow.display();
}

void Game::runWorld()
{
	int speed = -50;
	int koef = 0;
	
	if (plaYer.ReturnmIsMovingLeft())
		koef = 1;
	else if (plaYer.ReturnmIsMovingRight())
		koef = 3;
	else koef = 2;
	
	backGround.move(koef * speed * TimePerFrame.asSeconds(),0);
	backGroundTwo.move(koef * speed * TimePerFrame.asSeconds(),0);
	for (int i = 0; i < eneMies.size(); i++ ) 
		eneMies[i]->move((koef + 1) * speed * TimePerFrame.asSeconds());
}

void Game::collision()
{
	restart:
	for (int i = 0; i < bulLet.size(); i++)
		for (int j = 0; j < eneMies.size(); j++)
		{
			if ( bulLet.size() )	
				if ( abs(bulLet[i]->spriteBullet.getPosition().x - eneMies[j]->spriteEnemies.getPosition().x) <=5 &&
					(bulLet[i]->spriteBullet.getPosition().y - eneMies[j]->spriteEnemies.getPosition().y) <= 40 && 
					(bulLet[i]->spriteBullet.getPosition().y - eneMies[j]->spriteEnemies.getPosition().y) >= 5){
					
					eneMies[j]->LoweringHP( bulLet[i] );
					vector<Bullet*>::iterator itera = bulLet.begin();
					bulLet.erase( itera + i );
					plaYer.iteratorForBullet--;
					
					if ( eneMies[j]->GetHP() <= 0 ){
						vector<Enemy*>::iterator itera = eneMies.begin();
						eneMies.erase( itera + j );
					}
					goto restart; 
				}
		}
}