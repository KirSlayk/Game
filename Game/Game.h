#pragma once




using namespace std;

class Game
{
public:
	Game();
	void Run_Game();
	
private:
	void ProcessEvents_Game();
	void Update_Game();
	void Render_Game();
	void HandlePlayerInput_Game(sf::Keyboard::Key key, bool isPressed);
	void RunWorld_Game();
	void Collision_Game();
	void Shoting_Game();
	void BorderCheck_Game();
private:
	
	sf::RenderWindow mWindow;
	TextureHolder textures;
	TextureHolder texturBang;
	
	sf::Sprite backGround;
	sf::Sprite backGroundTwo;

	sf::Font font;
	
	sf::Time TimePerFrame; 
	
	vector<Enemy*> eneMies;
	vector<Bullet*> bulLet;
	Player plaYer;
	mMusic muSic;
	
	int speed;
	

	
};


