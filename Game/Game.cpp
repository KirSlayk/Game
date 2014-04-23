

#include "std.h"

Game::Game()
	: mWindow(sf::VideoMode(900, 600), "SFML Application")
	, textures()
{
	srand((unsigned) time(NULL));
	speed = 50;
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
	srand(time(NULL));
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	int timeForEneMies = 0;
	int numOfEnemy = 1;
	
	
	while (mWindow.isOpen())
	{
		if ( timeForEneMies  && timeForEneMies % 100 < 30 || !eneMies.size() )
		{
			numOfEnemy++;
			numOfEnemy = timeForEneMies% 3;
			if (eneMies.size() < 5 ){
				int size = eneMies.size();
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
		
		Shoting_Game();
		
		if ( eneMies.size() )
			for ( int i = 0; i < (int) eneMies.size(); i++)
			if ( abs( plaYer.ReturnSprite()->getPosition().x - eneMies[i]->ReturnSprite()->getPosition().x < 10 ) ){
				Collision_Game();
				break;
			}
		
		BorderCheck_Game();	
		timeForEneMies += clock.getElapsedTime().asMilliseconds()/5;
		Render_Game();
		
	}
}

void Game::Shoting_Game()
{
	
	if ( plaYer.GetmIsFire_Player() && bulLet.size() < 20 )
	{
		bulLet.push_back(new Bullet());
		bulLet[ bulLet.size() - 1 ]->ReturnSprite()->setPosition(plaYer.ReturnSprite()->getPosition().x + 65, plaYer.ReturnSprite()->getPosition().y + 32);
		plaYer.FalsemIsFire_Player();		
	}
}

void Game::BorderCheck_Game()
{
	
	
	
	if (  bulLet.size() )
		for ( int i = 0; i < (int) bulLet.size() - 1; i++ ){
			if ( bulLet[i]->ReturnSprite()->getPosition().x >= 900 && bulLet.at( i )  )
				bulLet.erase( bulLet.begin() + i );
		}
	
	if ( eneMies.size() )
		for ( int i = 0; i < (int) eneMies.size() - 1; i++ )
			if ( eneMies[i]->ReturnSprite()->getPosition().x < -10 )
				eneMies.erase( eneMies.begin() + i );
	
	if (backGround.getPosition().x <= -1150)
		backGround.setPosition(1200,0);
	if (backGroundTwo.getPosition().x <= -1150)
		backGroundTwo.setPosition(1200,0);

	if ( plaYer.ReturnSprite()->getPosition().x < 0 )
		plaYer.ReturnSprite()->setPosition( 0.0f, plaYer.ReturnSprite()->getPosition().y );
	if ( plaYer.ReturnSprite()->getPosition().x > 840 )
		plaYer.ReturnSprite()->setPosition( 840.0f, plaYer.ReturnSprite()->getPosition().y );
	if ( plaYer.ReturnSprite()->getPosition().y < 0 )
		plaYer.ReturnSprite()->setPosition( plaYer.ReturnSprite()->getPosition().x, 0.0f );
	if ( plaYer.ReturnSprite()->getPosition().y > 560 )
		plaYer.ReturnSprite()->setPosition( plaYer.ReturnSprite()->getPosition().x, 560.0f );
}


void Game::ProcessEvents_Game()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::KeyPressed:{
			muSic.VolumeWard_mMusic( event.key.code, true );				
			plaYer.HandlePlayerInput_Game( event.key.code, true );
			
								   }
								   break;
		case sf::Event::KeyReleased:{
			muSic.VolumeWard_mMusic( event.key.code, false );				
			plaYer.HandlePlayerInput_Game( event.key.code, false );
			
									}
									break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}


void Game::Update_Game()
{
	muSic.ChangeVolume_mMusic();
	plaYer.PlayerRun_Player();
	
	for ( int i = 0; i < (int) bulLet.size(); i++ )
		bulLet[i]->BulletRun_Bullet();
	for (int i = 0; i < (int) eneMies.size(); i++ ) 
		eneMies[i]->MoveEnemy_Enemy( &plaYer, eneMies[i] );	
	
	
	RunWorld_Game();

	
}


void Game::Render_Game()
{
	mWindow.clear();


	mWindow.draw(backGroundTwo);
	mWindow.draw(backGround);


	for ( int i = 0; i < (int) bulLet.size(); i++ )
		mWindow.draw(*(bulLet[i]->ReturnSprite()));
	
	mWindow.draw(*plaYer.ReturnSprite());
	
	for ( int i = 0; i < (int) eneMies.size(); i++ )
	{
		mWindow.draw(*(eneMies[i]->ReturnSprite()));
		if ( eneMies[i]->GetDeathTime_Enemy() )
		{
			if ( eneMies[i]->GetDeathTime_Enemy() > 74 )
				eneMies.erase( eneMies.begin() + i );
			
			else if ( eneMies[i]->GetDeathTime_Enemy() <= 74 )
				eneMies[i]->SwitchBang_Enemy();
		}
	}

	Text_Game();

	mWindow.display();
	
}

void Game::RunWorld_Game()
{
	sf::Vector2f movement(0.f,0.f);
	
	if (plaYer.GetmIsMovingLeft_Player())
		movement.x -= (float) 1.5*speed;
	else if (plaYer.GetmIsMovingRight_Player())
		movement.x -= (float) 3*speed;
	else movement.x -= (float) 2*speed;
	
	movement.x -= speed;
	
	backGround.move( movement * TimePerFrame.asSeconds() );
	backGroundTwo.move( movement * TimePerFrame.asSeconds() );
	
}

void Game::Collision_Game()
{
	
	for (int j = 0; j < (int)eneMies.size(); j++){
		restart:
		for (int i = 0; i < (int) bulLet.size(); i++)
		{
			if ( bulLet.size() )	
				if ( abs(bulLet[i]->ReturnSprite()->getPosition().x - eneMies[j]->ReturnSprite()->getPosition().x) <=5 &&
					(bulLet[i]->ReturnSprite()->getPosition().y - eneMies[j]->ReturnSprite()->getPosition().y) <= 40 && 
					(bulLet[i]->ReturnSprite()->getPosition().y - eneMies[j]->ReturnSprite()->getPosition().y) >= 5)
				{
					
					eneMies[j]->LoweringHP( eneMies[j] );
					
					bulLet.erase( bulLet.begin() + i );
					
					
					if ( eneMies[j]->GetHP() <= 0 && !eneMies[j]->GetDeathTime_Enemy() ){
						eneMies[j]->ReturnSprite()->setTexture(texturBang.Get(Textures::Bang));
						eneMies[j]->DeathTime_Enemy();
						plaYer.SetKilledEnemy_Player();
						
					}
					
					goto restart; 
				}
			}
			
		if ( abs(eneMies[j]->ReturnSprite()->getPosition().x - plaYer.ReturnSprite()->getPosition().x) <=65 &&
			abs(eneMies[j]->ReturnSprite()->getPosition().y - plaYer.ReturnSprite()->getPosition().y) <= 45 &&
			abs(eneMies[j]->ReturnSprite()->getPosition().y - plaYer.ReturnSprite()->getPosition().y) >=1 &&
			!eneMies[j]->GetDeathTime_Enemy())
			{
				eneMies[j]->ReturnSprite()->setTexture(texturBang.Get(Textures::Bang));

				eneMies[j]->DeathTime_Enemy();
				plaYer.LoweringHP( &plaYer );
				if ( plaYer.GetHP() <= 0 ){
					textures.Load( Textures::GameOver, "../Game/GameOver.png");
					sf::Sprite GameOverSprite;
					GameOverSprite.setTexture( textures.Get( Textures::GameOver ) );
					GameOverSprite.setPosition( 40.f, -1.f );
					
					
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
void Game::Text_Game()
{
	ostringstream str;
	ostringstream str2;
	if ( plaYer.GetHP() )
		str<< " HP "<<plaYer.GetHP();
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
	

	
	mWindow.draw( text );
	mWindow.draw( textTwo );
	
}