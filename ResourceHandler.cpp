#include "ResourceHandler.h"

std::map<std::string, sf::Font*> ResourceManager::s_fontMap = std::map<std::string, sf::Font*>();

sf::Font* ResourceManager::getFont(const std::string& key) {
	sf::Font* resource = nullptr;

	auto it = s_fontMap.find(key);
	if (it != s_fontMap.end()) { resource = it->second; }

	if (resource == nullptr) {
		// Create the resource
		resource = new sf::Font;

		if (!resource->loadFromFile("../assets/fonts/" + key + ".ttf")) {
			// If the above failed, try a different dir
			if (!resource->loadFromFile("assets/fonts/" + key + ".ttf")) {
				// If that failed, the resource does not exist
				return nullptr;
			}
		}

		s_fontMap.emplace(std::make_pair(key, resource));
	}

	return resource;
}