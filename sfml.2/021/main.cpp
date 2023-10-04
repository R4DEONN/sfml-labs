#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

using namespace std;

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
int main()
{
	sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Simple Event Loop");
	sf::Clock clock1;
	sf::Clock clock2;

	sf::Vector2f position = { 0, 350 };

	constexpr float BALL_SIZE = 40;
	sf::CircleShape ball(BALL_SIZE);
	ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

	float speedX = 100.f;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		constexpr float amplitudeY = 80.f;
		constexpr float periodY = 2;

		const float time = clock1.getElapsedTime().asSeconds();
		const float dt = clock2.restart().asSeconds();

		position.x = position.x + speedX * dt;
		if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speedX > 0))
		{
			speedX = -speedX;
		}
		if ((position.x < 0) && (speedX < 0))
		{
			speedX = -speedX;
		}

		const float wavePhase = time * float(2 * M_PI);
		const float y = amplitudeY * std::sin(wavePhase / periodY);
		const sf::Vector2f offset = { 0, y };

		ball.setPosition(position + offset);

		window.clear();
		window.draw(ball);
		window.display();
	}
}