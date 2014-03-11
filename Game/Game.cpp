#pragma once

#include "std.h"

Game::Game()
	: mWindow(sf::VideoMode(900, 600), "SFML Application")
	, textures()
{
	srand((unsigned) time(NULL));
	speed = 50;
	koef = 0.f;
	TimePerFrame = sf::seconds(1.f/10000.f);
	textures.Load(Textures::Landscape, "../Game/Cosmos2.png");
	backGround.setTexture(textures.Get(Textures::Landscape));
	backGround.setPosition(0.f,0.f);
	backGroundTwo.setTexture(textures.Get(Textures::Landscape));
	backGroundTwo.setPosition(1200.f,0.f);
	
	texturBang.Load(Textures::Bang,  "../Game/explosion.png");
	
	
	font.loadFromFile("../Game/MyFont.ttf");
	
}

void Game::Run_Game()
{
	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	int timeForEneMies = 0;
	int numOfEnemy = 1;
	
	
	
	while (mWindow.isOpen())
	{
		

		if ( timeForEneMies )
		{
			numOfEnemy = timeForEneMies % 3;
			if (eneMies.size() < 6 )
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
		
		ProcessEvents_Game();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			ProcessEvents_Game();
			Update_Game();
		}
		
		bulLet.shrink_to_fit();
		
		//cout<<bulLet.capacity()<<"\n";
		
		Shoting_Game();
		Collision_Game();
		BorderCheck_Game();	
		

		timeForEneMies = clock.getElapsedTime().asMilliseconds() / 5 ;
		
		
		Render_Game();
	}
}

void Game::Shoting_Game()
{
	if ( plaYer.GetmIsFire_Player() && bulLet.size() <20)
	{
		plaYer.iteratorForBullet++;
		bulLet.push_back(new Bullet());
		bulLet[ plaYer.iteratorForBullet ]->spriteBullet.setPosition(plaYer.ReturnSpritePlayer().getPosition().x + 65, plaYer.ReturnSpritePlayer().getPosition().y + 32);
		plaYer.FalsemIsFire_Player();		
		
	}
}

void Game::BorderCheck_Game()
{
	
	vector<Enemy*>::iterator iterator = eneMies.begin();
	
	if (  bulLet.size() )
		for ( int i = 0; i < bulLet.size() - 1; i++ ){
			vector<Bullet*>::iterator itera = bulLet.begin();
				if ( bulLet[i]->spriteBullet.getPosition().x >= 900 && bulLet.at( i )  )
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


void Game::ProcessEvents_Game()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::KeyPressed:
			plaYer.HandlePlayerInput_Game(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			plaYer.HandlePlayerInput_Game(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
		}
	}
}


void Game::Update_Game()
{
	plaYer.PlayerRun_Player();
	
	for ( int i = 0; i < bulLet.size(); i++ )
		bulLet[i]->BulletRun_Bullet();
	for (int i = 0; i < eneMies.size(); i++ ) 
		eneMies[i]->MoveEnemy_Enemy( &plaYer );	
	
	
	RunWorld_Game();
}


void Game::Render_Game()
{
	ostringstream str;
	ostringstream str2;
	if ( plaYer.GetHP_Player() )
		str<< " HP "<<plaYer.GetHP_Player();
	str2<< "Slain Enemies "<< plaYer.GetNumOfKilledEnemy_Player();

	sf::Text text;
	sf::Text textTwo;
	
	text.setFont( font );
	text.setCharacterSize( 15 );
	text.setColor( sf::Color::Yellow );
	text.setStyle( sf::Text::Bold );
	text.setPosition( 0.f, 0.f );
	text.setString(str.str());

	textTwo = text;
	textTwo.setPosition( 750.f, 0.f );
	textTwo.setString(str2.str());
	
	mWindow.clear();


	mWindow.draw(backGroundTwo);
	mWindow.draw(backGround);

	for ( int i = 0; i < bulLet.size(); i++ )
		mWindow.draw(bulLet[i]->spriteBullet);
	
	mWindow.draw(plaYer.ReturnSpritePlayer());
	
	for ( int i = 0; i < eneMies.size(); i++ )
	{
		mWindow.draw(eneMies[i]->spriteEnemies);
		if ( eneMies[i]->GetDeathTime_Enemy() )
		{
			if ( eneMies[i]->GetDeathTime_Enemy() > 74 )
			{
			vector<Enemy*>::iterator itera = eneMies.begin();
			eneMies.erase( itera + i );
			}
			else if ( eneMies[i]->GetDeathTime_Enemy() <= 74 )
				eneMies[i]->SwitchBang_Enemy();
		}
	}

	mWindow.draw( text );
	mWindow.draw( textTwo );
	mWindow.display();
	
}

void Game::RunWorld_Game()
{
	sf::Vector2f movement(0.f,0.f);
	
	if (plaYer.GetmIsMovingLeft_Player())
		koef = 1.f;
	else if (plaYer.GetmIsMovingRight_Player())
		koef = 3.f;
	else koef = 2.f;
	
	movement.x -= speed;
	
	backGround.move( koef * movement * TimePerFrame.asSeconds() );
	backGroundTwo.move( koef * movement * TimePerFrame.asSeconds() );
	
}

void Game::Collision_Game()
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
					
					eneMies[j]->LoweringHP_Enemy( bulLet[i] );
					vector<Bullet*>::iterator itera = bulLet.begin();
					bulLet.erase( itera + i );
					plaYer.iteratorForBullet--;
					
					if ( eneMies[j]->GetHP_Enemy() <= 0 && !eneMies[j]->GetDeathTime_Enemy() ){
						eneMies[j]->spriteEnemies.setTexture(texturBang.Get(Textures::Bang));
						eneMies[j]->DeathTime_Enemy();
						plaYer.SetKilledEnemy_Player();
						
					}
					goto restart; 
				}
			}
			
		if ( abs(eneMies[j]->spriteEnemies.getPosition().x - plaYer.ReturnSpritePlayer().getPosition().x) <=65 &&
			abs(eneMies[j]->spriteEnemies.getPosition().y - plaYer.ReturnSpritePlayer().getPosition().y) <= 45 &&
			abs(eneMies[j]->spriteEnemies.getPosition().y - plaYer.ReturnSpritePlayer().getPosition().y) >=1 &&
			!eneMies[j]->GetDeathTime_Enemy())
			{
				eneMies[j]->spriteEnemies.setTexture(texturBang.Get(Textures::Bang));
				eneMies[j]->DeathTime_Enemy();
				plaYer.LowingHP_Player();
				if ( plaYer.GetHP_Player() <= 0 ){
					textures.Load( Textures::GameOver, "../Game/GameOver.png");
					sf::Sprite GameOverSprite;
					GameOverSprite.setTexture( textures.Get( Textures::GameOver ) );
					GameOverSprite.setPosition( 40.f, -1.f );
					sf::Event event;
					int c;
					while ( mWindow.isOpen() ){
						mWindow.clear();
						mWindow.draw( GameOverSprite );
						mWindow.display();
						ProcessEvents_Game();
					}
				}
			}	
	}
	
}
