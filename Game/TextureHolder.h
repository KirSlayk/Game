#pragma once


namespace Textures
{
	enum ID{ Landscape, Airplane, Missile, Enemy, Bullet, Bang };
}

class TextureHolder
{
public:
	void Load(Textures::ID id, const std::string& filename);
	sf::Texture& Get(Textures::ID id);
	const sf::Texture& Get(Textures::ID id) const;
private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

