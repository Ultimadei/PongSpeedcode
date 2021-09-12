#include "Player.h"
#include "ResourceHandler.h"

Player::Player(const sf::Vector2f& position) :
	m_score(0)
{
	setPosition(position);
	m_paddle.setPosition(0.0f, 300.0f);
	m_scoreText.setFont(*ResourceManager::getFont("ariel"));
	//m_scoreText.setPosition(sf::Vector2f(12.5f, 50.0f));
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setCharacterSize(60);
	addScore(0);
}

const sf::FloatRect Player::getPaddleCollisionBounds() const {
	return sf::FloatRect(getPosition() + m_paddle.getPosition() - (m_paddle.getSize() * 0.5f), m_paddle.getSize());
}

Paddle& Player::getPaddle() {
	return m_paddle;
}

void Player::addScore(int gained) {
	m_score += gained;

	m_scoreText.setString(std::to_string(m_score));

	const sf::FloatRect textBounds = m_scoreText.getLocalBounds();
	//m_scoreText.setOrigin(textBounds.left + textBounds.width * 0.5f, textBounds.top + textBounds.height * 0.5f);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform.combine(getTransform());

	target.draw(m_scoreText, states);
	target.draw(m_paddle, states);
}