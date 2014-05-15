

#include "std.h"



mMusic::mMusic()
{
	volume = 10;
	deltaVolume = 5;
	isUpVolume = false;
	isDownVolume = false;
	isPause = false;
	music.openFromFile( "../Game/StarWars.ogg" );
	music.setVolume( volume );
	music.setLoop( true );
	music.play();
	
}

void mMusic::VolumeWard_mMusic( sf::Keyboard::Key key, bool isPressed )
{
	if ( key == sf::Keyboard::Up )
		isUpVolume = isPressed;
	if ( key == sf::Keyboard::Down )
		isDownVolume = isPressed;
	if ( key == sf::Keyboard::P )
		isPause = isPressed;
}

void mMusic::ChangeVolume_mMusic()
{
	if ( isUpVolume ){
		music.setVolume( volume += deltaVolume );
		isUpVolume = false;
	}
	else if ( isDownVolume && volume > 0 ){
		music.setVolume ( volume -= deltaVolume );
		isDownVolume = false;
	}
}