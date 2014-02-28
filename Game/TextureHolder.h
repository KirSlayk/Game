#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>;

namespace Textures
{
	enum ID{ Landscape, Airplane, Missile, Enemies };
}

class TextureHolder
{
public:
	void load(Textures::ID id, const std::string& filename);
	sf::Texture& get(Textures::ID id);
	const sf::Texture& get(Textures::ID id) const;
private:
	std::map<Textures::ID,
	std::unique_ptr<sf::Texture>> mTextureMap;
};

void TextureHolder::load(Textures::ID id, const std::string& filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	texture->loadFromFile(filename);
	mTextureMap.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture& TextureHolder::get(Textures::ID id)
{
	auto found = mTextureMap.find(id);
	return *found->second;
}
