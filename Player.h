#pragma once

#include "Paddle.h"

class Player :
	public sf::Drawable,
	protected sf::Transformable {
public:
	Player(const sf::Vector2f& position);

	// Returns an sf::FloatRect compatible with collision functions
	const sf::FloatRect getPaddleCollisionBounds() const;

	Paddle& getPaddle();

	void addScore(int gained);
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	Paddle m_paddle;

	int m_score;
	sf::Text m_scoreText;
};