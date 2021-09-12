#include <math.h>

#include "Ball.h"

Ball::Ball(float radius, float speed) :
	sf::CircleShape(radius),
    m_direction(1.0f, 0.0f),
    m_speed(speed)
{
    setFillColor(sf::Color(200, 200, 200, 255)); // Opaque grey
    setOrigin(radius, radius);
}

void Ball::reset(const sf::Vector2f& position, const sf::Vector2f& direction, float speed) {
    setPosition(position);
    setDirection(direction);
    if (speed != 0.0f) {
        setSpeed(speed);
    }
}

bool Ball::collideRectangle(const sf::FloatRect& target) const {
    const sf::Vector2f position = getPosition();
    const float radius = getRadius();

    // Distance between circle's center and the rectangle's center
    const sf::Vector2f circleDistance(
        std::abs(position.x - (target.left + target.width * 0.5f)), 
        std::abs(position.y - (target.top + target.height * 0.5f))
    );

    // Check the case where the distance is too far to possibly collide

    if (circleDistance.x > ((target.width * 0.5f) + radius)) { return false; }
    if (circleDistance.y > ((target.height * 0.5f) + radius)) { return false; }

    // Check the case where the distance is so close it must collide

    if (circleDistance.x <= (target.width * 0.5f)) { return true; }
    if (circleDistance.y <= (target.height * 0.5f)) { return true; }

    // Finally check the case where the circle intersects a corner of the rectangle
    // Square values to avoid using expensive square root function

    float cornerDistance_sq = std::pow(circleDistance.x - target.width * 0.5f, 2.0f) +
        std::pow(circleDistance.y - target.height * 0.5f, 2.0f);

    return (cornerDistance_sq <= std::pow(radius, 2.0f));
}

void Ball::bounce(const sf::FloatRect& target) {
    float yDir = (getPosition().y - (target.top + target.height * 0.5f)) / target.height;
    float xDir = std::sqrt(1 - std::pow(yDir, 2.0f));

    if (m_direction.x >= 0.0f) {
        // Invert x direction
        xDir *= -1.0f;
    }

    setDirection(sf::Vector2f(xDir, yDir));
}

void Ball::setSpeed(float speed) {
    m_speed = speed;
}

void Ball::setDirection(const sf::Vector2f& direction) {
    m_direction = direction;
}

void Ball::update(float dt) {
    move(m_direction * m_speed);
}