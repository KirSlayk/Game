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
	void update();
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void runWorld();
	void collision();
	void shoting();
	void borderCheck();
private:
	
	sf::RenderWindow mWindow;
	TextureHolder textures;
	TextureHolder texturBang;
	
	sf::Sprite backGround;
	sf::Sprite backGroundTwo;

	sf::Time TimePerFrame; 
	
	vector<Enemy*> eneMies;
	vector<Bullet*> bulLet;
	Player plaYer;
	
	int speed;
	float koef;
	int timeForEneMies;
	int numOfEnemy;
};


Game::Game()
	: mWindow(sf::VideoMode(900, 600), "SFML Application")
	, textures()
{
	srand(time(NULL));
	speed = 50;
	koef = 0.f;
	TimePerFrame = sf::seconds(1.f/10000.f);
	textures.load(Textures::Landscape, "C:/work/Game/Game/Cosmos2.png");
	backGround.setTexture(textures.get(Textures::Landscape));
	backGround.setPosition(0.f,0.f);
	backGroundTwo.setTexture(textures.get(Textures::Landscape));
	backGroundTwo.setPosition(1200.f,0.f);

	int timeForEneMies = 0;
	numOfEnemy = 1;
	texturBang.load(Textures::Bang,  "C:/work/Game/Game/explosion.png");
}

void Game::run()
{
	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	
	
	
	
	while (mWindow.isOpen())
	{
		
		
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update();
		}
		
		bulLet.shrink_to_fit();
		cout<<bulLet.capacity()<<"\n";
		shoting();
		collision();
		borderCheck();	
		

		timeForEneMies = clock.getElapsedTime().asMilliseconds() / 5 ;
		
		
		render();
	}
}

void Game::shoting()
{
	if ( plaYer.GetmIsFire() && bulLet.size() <20)
	{
		plaYer.iteratorForBullet++;
		bulLet.push_back(new Bullet());
		bulLet[ plaYer.iteratorForBullet ]->spriteBullet.setPosition(plaYer.ReturnSpritePlayer().getPosition().x + 65, plaYer.ReturnSpritePlayer().getPosition().y + 32);
		plaYer.FalsemIsFire();		
		
	}
}

void Game::borderCheck()
{
	
	vector<Enemy*>::iterator iterator = eneMies.begin();
	
	if (  bulLet.size() )
		for ( int i = 0; i < bulLet.size() - 1; i++ ){
			vector<Bullet*>::iterator itera = bulLet.begin();
				if ( bulLet[i]->spriteBullet.getPosition().x >= 900 && bulLet.at( i ) )
				{
						bulLet.erase( itera );
						plaYer.iteratorForBullet--;
					
				}
			}
	
	for ( int i = 0; i < eneMies.size(); i++ )
		if ( eneMies.size() )
			if ( eneMies[i]->spriteEnemies.getPosition().x < -100 )
				eneMies.erase( iterator + i );
	
	if (backGround.getPosition().x <= -1150)
		backGround.setPosition(1200,0);
	if (backGroundTwo.getPosition().x <= -1150)
		backGroundTwo.setPosition(1200,0);
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


void Game::update()
{
	if ( timeForEneMies )
		{
			numOfEnemy = timeForEneMies % 3;
			if (eneMies.size() < 8 )
				if ( eneMies.empty() )	
					for (int i = 0; i < numOfEnemy - 1; ++i)
						eneMies.push_back(new Enemy());
				else {
					int size = eneMies.size();
					eneMies.back();
					for ( int i = size; i < size + numOfEnemy - 1; i++ )
						eneMies.push_back(new Enemy());
				}
		}
	
	
	
	plaYer.PlayerRun();
	
	for ( int i = 0; i < bulLet.size(); i++ )
		bulLet[i]->BulletRun();
	for (int i = 0; i < eneMies.size(); i++ ) 
		eneMies[i]->moveEnemy( &plaYer );	
	
	
	runWorld();
}


void Game::render()
{
	
	mWindow.clear();

	mWindow.draw(backGroundTwo);
	mWindow.draw(backGround);

	for ( int i = 0; i < bulLet.size(); i++ )
		mWindow.draw(bulLet[i]->spriteBullet);
	
	mWindow.draw(plaYer.ReturnSpritePlayer());
	
	for ( int i = 0; i < eneMies.size(); i++ )
	{
		mWindow.draw(eneMies[i]->spriteEnemies);
		if ( eneMies[i]->GetDeathTime() )
		{
			if ( eneMies[i]->GetDeathTime() > 74 )
			{
			vector<Enemy*>::iterator itera = eneMies.begin();
			eneMies.erase( itera + i );
			}
			else if ( eneMies[i]->GetDeathTime() <= 74 )
				eneMies[i]->SwitchBang();
		}
	}
	mWindow.display();
}

void Game::runWorld()
{
	sf::Vector2f movement(0.f,0.f);
	
	if (plaYer.ReturnmIsMovingLeft())
		koef = 1.f;
	else if (plaYer.ReturnmIsMovingRight())
		koef = 3.f;
	else koef = 2.f;
	
	movement.x -= speed;
	
	backGround.move( koef * movement * TimePerFrame.asSeconds() );
	backGroundTwo.move( koef * movement * TimePerFrame.asSeconds() );
	
}

void Game::collision()
{
	
	for (int j = 0; j < eneMies.size(); j++){
		restart:
		for (int i = 0; i < bulLet.size(); i++)
		{
			if ( bulLet.size() )	
				if ( abs(bulLet[i]->spriteBullet.getPosition().x - eneMies[j]->spriteEnemies.getPosition().x) <=5 &&
					(bulLet[i]->spriteBullet.getPosition().y - eneMies[j]->spriteEnemies.getPosition().y) <= 40 && 
					(bulLet[i]->spriteBullet.getPosition().y - eneMies[j]->spriteEnemies.getPosition().y) >= 5)
				{
					
					eneMies[j]->LoweringHP( bulLet[i] );
					vector<Bullet*>::iterator itera = bulLet.begin();
					bulLet.erase( itera + i );
					plaYer.iteratorForBullet--;
					
					if ( eneMies[j]->GetHP() <= 0 && !eneMies[j]->GetDeathTime() ){
						eneMies[j]->spriteEnemies.setTexture(texturBang.get(Textures::Bang));
						eneMies[j]->DeathTime();
						
					}
					goto restart; 
				}
		}
	}
}
