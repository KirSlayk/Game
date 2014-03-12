#pragma once

class mMusic
{
public:
	mMusic();
	void VolumeWard_mMusic( sf::Keyboard::Key key, bool isPressed );
	void ChangeVolume_mMusic();
private:
	sf::Music music;
	float volume;
	float deltaVolume;
	bool isUpVolume, isDownVolume;
};

