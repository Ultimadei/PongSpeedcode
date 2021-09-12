#pragma once

#include <SFML/Graphics.hpp>

class Paddle :
	public sf::RectangleShape {
public:
	Paddle();
	~Paddle();

	// Clamps the paddle to be within 'distance' of its starting position
	void clamp(float distance);
private:
};