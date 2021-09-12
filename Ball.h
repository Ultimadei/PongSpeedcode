#pragma once

#include <SFML/Graphics.hpp>

class Ball :
	public sf::CircleShape {
public:
	Ball(float radius, float speed);

	// Resets the ball. If speed is 0.0, the same speed is kept instead
	void reset(const sf::Vector2f& position, const sf::Vector2f& direction, float speed = 0.0f);

	// Returns true if the ball collides with the rectangle
	bool collideRectangle(const sf::FloatRect& target) const;

	// Bounce off target
	void bounce(const sf::FloatRect& target);

	void setSpeed(float speed);
	void setDirection(const sf::Vector2f& direction);

	void update(float dt);
private:
	sf::Vector2f m_direction;
	float m_speed;
};