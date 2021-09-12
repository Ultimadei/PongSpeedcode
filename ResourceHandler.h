#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class ResourceManager {
public:
	static sf::Font* getFont(const std::string& key);
private:
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	static std::map<std::string, sf::Font*> s_fontMap;
};