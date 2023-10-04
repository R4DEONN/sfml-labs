#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

using namespace std;

int main()
{
	constexpr unsigned WINDOW_WIDTH = 800;
	constexpr unsigned WINDOW_HEIGHT = 600;
	constexpr int pointCount = 360;
	const sf::Vector2f ellipseRadius = {200.f, 80.f};

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(
		sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
		"Ellipse",
		sf::Style::Default, settings);

	sf::ConvexShape shape;
	shape.setPosition({ 400, 320 });
	shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

	shape.setPointCount(pointCount);
	for (int pointN = 0; pointN < pointCount; pointN++)
	{
		float angle = float(2 * M_PI * pointN) / float(pointCount);
		sf::Vector2f point = sf::Vector2f{
			ellipseRadius.x * std::sin(angle),
			ellipseRadius.y * std::cos(angle),
		};
		shape.setPoint(pointN, point);
	}

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

		window.clear();
		window.draw(shape);
		window.display();
	}
}