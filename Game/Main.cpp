#include <SFML/Graphics.hpp>
#include <iostream>;

class Game
{
public:
	Game();
	void run();
	bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight;
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	sf::Sprite mPlayer;
	sf::Time TimePerFrame; 

	
};

Game::Game()
	: mWindow(sf::VideoMode(640, 480), "SFML Application")
	, mPlayer()
	, mTexture()
{
	if (!mTexture.loadFromFile("C:/work/Game/Game/alienblaster.png"))
	{
		// Handle loading error
	}
	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(110.f, 110.f);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	TimePerFrame = sf::seconds(1.f/60.f);
	mWindow.setVerticalSyncEnabled(true);
	while (mWindow.isOpen())
	{
		//sf::Time deltaTime = clock.restart();
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
	if (mIsMovingUp)
		movement.y -= 30.f;
	if (mIsMovingDown)
		movement.y += 30.f;
	if (mIsMovingLeft)
		movement.x -= 30.f;
	if (mIsMovingRight)
		movement.x += 30.f;
	mPlayer.move(movement * TimePerFrame.asSeconds());
}

void Game::render()
{
	
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}

void main()
{
	Game game;
	game.run();

}


