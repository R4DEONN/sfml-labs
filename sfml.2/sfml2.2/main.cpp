#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

using namespace std;

int main()
{
	constexpr unsigned WINDOW_WIDTH = 800;
	constexpr unsigned WINDOW_HEIGHT = 600;
	constexpr int pointCount = 200;
	float radius;
	sf::Clock clock;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(
		sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
		"Ellipse",
		sf::Style::Default, settings);

	int circlePoint = 0;
	const float circleRadius = 50;
	const sf::Vector2f position {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
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

		constexpr float speed = 10.f;

		const float dt = clock.getElapsedTime().asSeconds();

		float circleAngle = float(2 * M_PI) * dt;
		if (circleAngle >= float(2 * M_PI))
		{
			clock.restart();
		}
		sf::Vector2f offset = sf::Vector2f{
			circleRadius * sin(circleAngle),
			circleRadius * cos(circleAngle),
		};

		sf::ConvexShape shape;
		shape.setPosition(position + offset);
		shape.setFillColor(sf::Color(0xFF, 0x09, 0x80));

		shape.setPointCount(pointCount);
		for (int pointN = 0; pointN < pointCount; pointN++)
		{
			float angle = float(2 * M_PI * pointN) / float(pointCount);
			radius = 200 * sin(6 * angle);
			sf::Vector2f point = sf::Vector2f{
				radius * sin(angle),
				radius * cos(angle),
			};
			shape.setPoint(pointN, point);
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
}