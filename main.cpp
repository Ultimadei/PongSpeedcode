#include <vector>
#include <random>

#include "Player.h"
#include "Ball.h"

constexpr float TARGET_FPS = 60.0f;
constexpr float WINDOW_WIDTH = 800.0f;
constexpr float WINDOW_HEIGHT = 600.0f;

float getRand(float min, float max);

sf::Vector2f getRandomDirection(float forceX = 0.0f);

int main(int argc, char** argv) {
	sf::RenderWindow win(sf::VideoMode((unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT), "Pong");
	win.setFramerateLimit((unsigned int)TARGET_FPS);

	Player player1(sf::Vector2f(100.0f, 0.0f));
	Player player2(sf::Vector2f(675.0f, 0.0f));

	// Start in the center
	const sf::Vector2f ballStartPosition(400.0f, 300.0f);

	Ball ball(20.0f, 0.0f);
	ball.reset(ballStartPosition, sf::Vector2f(1.0f, 0.0f), 5.0f);

	sf::Clock clock;

	const sf::FloatRect topWall(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(WINDOW_WIDTH, 1.0f));
	const sf::FloatRect bottomWall(sf::Vector2f(0.0f, WINDOW_HEIGHT - 1.0f), sf::Vector2f(WINDOW_WIDTH, 1.0f));

	const sf::FloatRect leftWall(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1.0f, WINDOW_HEIGHT));
	const sf::FloatRect rightWall(sf::Vector2f(WINDOW_WIDTH - 1.0f, 0.0f), sf::Vector2f(1.0f, WINDOW_HEIGHT));

	const float paddleSpeed = 10.0f;

	bool playing = true;

	while (win.isOpen()) {
		sf::Event evnt;
		while (win.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				win.close();
				break;
			case sf::Event::KeyPressed:
				switch (evnt.key.code) {
				case sf::Keyboard::Escape:
					playing = false;
					break;
				case sf::Keyboard::W:
					player1.getPaddle().move(sf::Vector2f(0.0f, -paddleSpeed));
					break;
				case sf::Keyboard::S:
					player1.getPaddle().move(sf::Vector2f(0.0f, paddleSpeed));
					break;
				case sf::Keyboard::Up:
					player2.getPaddle().move(sf::Vector2f(0.0f, -paddleSpeed));
					break;
				case sf::Keyboard::Down:
					player2.getPaddle().move(sf::Vector2f(0.0f, paddleSpeed));
					break;
				}
				break;
			}
		}

		if (playing) {
			float dt = TARGET_FPS * clock.restart().asSeconds();

			ball.update(dt);

			// Collision checks

			const sf::FloatRect player1Paddle = player1.getPaddleCollisionBounds();
			const sf::FloatRect player2Paddle = player2.getPaddleCollisionBounds();

			if (ball.collideRectangle(player1Paddle)) {
				ball.bounce(player1Paddle);
			}
			else if (ball.collideRectangle(player2Paddle)) {
				ball.bounce(player2Paddle);
			}
			else if (ball.collideRectangle(topWall)) {
				ball.move(sf::Vector2f(0.0f, WINDOW_HEIGHT - ball.getRadius() * 2.0f));
			}
			else if (ball.collideRectangle(bottomWall)) {
				ball.move(sf::Vector2f(0.0f, -(WINDOW_HEIGHT - ball.getRadius() * 2.0f)));
			}
			// Give points
			else if (ball.collideRectangle(leftWall)) {
				player2.addScore(1);
				ball.reset(ballStartPosition, getRandomDirection());
			}
			else if (ball.collideRectangle(rightWall)) {
				player1.addScore(1);
				ball.reset(ballStartPosition, getRandomDirection());
			}
		}

		win.clear(sf::Color::Black);
		win.draw(player1);
		win.draw(player2);
		win.draw(ball);
		win.display();
	}

	return 0;
}

float getRand(float min, float max) {
	static std::random_device randDev;
	static std::mt19937 rng(randDev());
	std::uniform_real_distribution<float> distribution(min, max);

	return distribution(rng);
}

sf::Vector2f getRandomDirection(float forceX) {
	float x = forceX;
	float y = 0.0f;

	std::srand(std::time(0));

	if (forceX == 0.0f) {
		x = getRand(0.0f, 1.0f);
	}
	else {
		y = getRand(0.0f, 1.0f);
		
		// Normalize
		float mag = std::sqrt(std::pow(x, 2.0f) + std::pow(y, 2.0f));

		return sf::Vector2f(x / mag, y / mag);
	}
	y = std::sqrt(1 - std::pow(x, 2.0f));

	return sf::Vector2f(x, y);
}