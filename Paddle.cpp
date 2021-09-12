#include "Paddle.h"

Paddle::Paddle() :
	sf::RectangleShape(sf::Vector2f(25.0f, 150.0f))
{
	setFillColor(sf::Color::White);

	const sf::Vector2f size = getSize();
	// Set origin to the center of the paddle
	setOrigin(size.x * 0.5f, size.y * 0.5f);
}

Paddle::~Paddle()
{
}